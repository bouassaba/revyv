use std::{
    collections::VecDeque,
    sync::mpsc::{self, Receiver, Sender},
    thread,
};

pub enum RequestType {
    RegisterClient = 1,
    CreateWindow = 3,
    MoveWindow = 4,
    ResizeWindow = 5,
    UpdateWindowPixels = 6,
    SetWindowVisibility = 7,
    DestroyWindow = 8,
    BringWindowToFront = 9,
}

pub struct Payload {
    pid: i32,
    request_type: u8,
    window_id: u32,
    field0: f32,
    field1: f32,
    field2: f32,
    field3: f32,
    field4: i8,
    field5: u64,
    field6: u64,
}

pub struct Listener {
    socket: zmq::Socket,
    payloads: VecDeque<Payload>,
    tx: Sender<Payload>,
    rx: Receiver<Payload>,
}

impl Listener {
    pub fn new() -> Self {
        let context = zmq::Context::new();
        let socket = context.socket(zmq::PULL).unwrap();
        if !socket.set_sndtimeo(10000).is_ok() {
            panic!()
        }
        if !socket.set_rcvtimeo(10000).is_ok() {
            panic!()
        }
        if !socket.bind("tcp://*:12345").is_ok() {
            panic!()
        }
        let (tx, rx) = mpsc::channel::<Payload>();
        thread::spawn(move || {});
        Self {
            socket,
            payloads: VecDeque::new(),
            tx,
            rx,
        }
    }

    pub fn process_message(&mut self, payload: &Payload) {
        let mut msg = zmq::Message::new();
        self.socket.recv(&mut msg, 0).unwrap();
    }
}
