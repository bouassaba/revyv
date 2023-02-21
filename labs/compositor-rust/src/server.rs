use crate::compositor::Compositor;
use crate::event_source::{Event, EventSource};
use crate::listener::Listener;
use crate::publisher::Publisher;
use std::time::Duration;

pub struct Server {
    event_source: EventSource,
    compositor: Compositor,
    listener: Listener,
    publishers: Vec<Publisher>,
    pids: Vec<i32>,
}

impl Server {
    pub fn new() -> Self {
        let sdl_context = sdl2::init().unwrap();
        let event_source = EventSource::new(&sdl_context);
        let compositor = Compositor::new(&sdl_context);
        Self {
            event_source,
            compositor,
            pids: Vec::new(),
            publishers: Vec::new(),
            listener: Listener::new(),
        }
    }

    pub fn run(&mut self) {
        'running: loop {
            self.compositor.compose();
            let event = self.event_source.poll_event();
            match event {
                Some(Event::Quit) => {
                    break 'running;
                }
                _ => {}
            }
            std::thread::sleep(Duration::new(0, 1_000_000_000u32 / 60));
        }
    }
}
