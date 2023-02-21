use sdl2::{event::Event as SdlEvent, mouse::MouseButton, EventPump, Sdl};

pub enum MouseButtonType {
    Unknown,
    Left,
    Right,
    Middle,
}

pub enum MouseButtonState {
    Down,
    Up,
}

pub enum KeyState {
    Down,
    Up,
}

pub enum Event {
    Quit,
    MouseMove {
        x: i32,
        y: i32,
    },
    MouseButton {
        x: i32,
        y: i32,
        button: MouseButtonType,
        state: MouseButtonState,
        clicks: u8,
    },
    MouseScroll {
        x: i32,
        y: i32,
        scroll_x: i32,
        scroll_y: i32,
    },
    Text {
        text: String,
    },
    Key {
        scancode: i32,
        keycode: i32,
        keymod: u16,
        state: KeyState,
    },
}

pub struct EventSource {
    event_pump: EventPump,
    mouse_x: i32,
    mouse_y: i32,
}

impl EventSource {
    pub fn new(sdl_context: &Sdl) -> Self {
        Self {
            event_pump: sdl_context.event_pump().unwrap(),
            mouse_x: 0,
            mouse_y: 0,
        }
    }

    pub fn poll_event(&mut self) -> Option<Event> {
        for event in self.event_pump.poll_iter() {
            return self.parse_sdl_event(event);
        }
        None
    }

    fn parse_sdl_event(&self, event: SdlEvent) -> Option<Event> {
        match event {
            SdlEvent::Quit { .. }
            | SdlEvent::KeyDown {
                keycode: Some(sdl2::keyboard::Keycode::Escape),
                ..
            } => Some(Event::Quit),
            SdlEvent::MouseMotion { x, y, .. } => Some(Event::MouseMove { x, y }),
            SdlEvent::MouseButtonDown {
                mouse_btn,
                clicks,
                x,
                y,
                ..
            } => Some(Event::MouseButton {
                x,
                y,
                button: self.parse_sdl_mouse_button(mouse_btn),
                state: MouseButtonState::Down,
                clicks,
            }),
            SdlEvent::MouseButtonUp {
                mouse_btn,
                clicks,
                x,
                y,
                ..
            } => Some(Event::MouseButton {
                x,
                y,
                button: self.parse_sdl_mouse_button(mouse_btn),
                state: MouseButtonState::Up,
                clicks,
            }),
            SdlEvent::MouseWheel { x, y, .. } => Some(Event::MouseScroll {
                x: self.mouse_x,
                y: self.mouse_y,
                scroll_x: x,
                scroll_y: y,
            }),
            SdlEvent::KeyDown {
                keycode,
                scancode,
                keymod,
                ..
            } => Some(Event::Key {
                scancode: scancode.unwrap() as i32,
                keycode: keycode.unwrap() as i32,
                keymod: keymod.bits(),
                state: KeyState::Down,
            }),
            SdlEvent::KeyUp {
                keycode,
                scancode,
                keymod,
                ..
            } => Some(Event::Key {
                scancode: scancode.unwrap() as i32,
                keycode: keycode.unwrap() as i32,
                keymod: keymod.bits(),
                state: KeyState::Up,
            }),
            SdlEvent::TextInput { text, .. } => Some(Event::Text { text }),
            _ => None,
        }
    }

    fn parse_sdl_mouse_button(&self, mouse_button: sdl2::mouse::MouseButton) -> MouseButtonType {
        match mouse_button {
            MouseButton::Left => MouseButtonType::Left,
            MouseButton::Right => MouseButtonType::Right,
            MouseButton::Middle => MouseButtonType::Middle,
            MouseButton::Unknown => MouseButtonType::Unknown,
            _ => MouseButtonType::Unknown,
        }
    }
}
