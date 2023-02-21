use crate::event_source::Event;

pub enum EventType {
    MouseMove = 1,
    MouseButton = 2,
    MouseScroll = 3,
    Key = 4,
    Text = 5,
    Quit = 6,
}

pub struct Payload {
    window_id: u32,
    event_type: u8,
    field0: f32,
    field1: f32,
    field2: f32,
    field3: f32,
    field4: u8,
    field5: u8,
    field6: u8,
    field7: u32,
}

pub struct Publisher {}

impl Publisher {
    pub fn new() -> Self {
        Self {}
    }

    pub fn publish_mouse_move_event(event: &Event) {}

    pub fn publish_mouse_button_event(event: &Event) {}

    pub fn publish_mouse_scroll_event(event: &Event) {}

    pub fn publish_text_event(event: &Event) {}

    pub fn publish_key_event(event: &Event) {}
}
