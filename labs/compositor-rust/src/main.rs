mod compositor;
mod event_source;
mod listener;
mod publisher;
mod server;

use server::Server;

pub fn main() {
    Server::new().run()
}
