cd "$(dirname "$0")"
cd client
pio run -t upload
cd ..
cd server
cargo run
