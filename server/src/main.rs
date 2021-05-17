#![feature(proc_macro_hygiene, decl_macro)]
use rocket::State;
use rocket_contrib::templates::Template;
use serde::{Deserialize, Serialize};
use std::collections::HashMap;
use std::net::UdpSocket;
use std::sync::Mutex;

struct SharedContext {
    mode: Mutex<Option<u8>>,
}

impl SharedContext {
    fn to_template(&self) -> Option<TemplateContext> {
        let shared_mode: Option<u8> = *self.mode.lock().unwrap();
        match shared_mode {
            Some(m) => Some(TemplateContext { mode: m }),
            None => None,
        }
    }
}

#[derive(Serialize, Deserialize)]
struct TemplateContext {
    mode: u8,
}

#[macro_use]
extern crate rocket;
use rocket::http::RawStr;

#[get("/")]
fn index(state: State<SharedContext>) -> Template {
    let data: &SharedContext = state.inner();
    let context = data.to_template();
    match context {
        Some(c) => Template::render("index", &c),
        None => Template::render("index", HashMap::<&str, &str>::new()),
    }
}

#[get("/send?<ip>&<modecmd>")]
fn send(state: State<SharedContext>, ip: &RawStr, modecmd: u8) -> Template {
    println!("{}", ip.as_str());
    let socket =
        UdpSocket::bind("0.0.0.0:3400").expect("Error: failed to bind to ESP8266 address.");
    socket
        .send_to(&[modecmd; 1], ip.as_str())
        .expect("Error: failed to send mode.");
    let data: &SharedContext = state.inner();
    *data.mode.lock().unwrap() = Some(modecmd);

    let context = data.to_template();
    Template::render("index", &context)
}

fn main() {
    let context = SharedContext {
        mode: Mutex::new(None),
    };
    rocket::ignite()
        .mount("/", routes![index])
        .mount("/", routes![send])
        .attach(Template::fairing())
        .manage(context)
        .launch();
}
