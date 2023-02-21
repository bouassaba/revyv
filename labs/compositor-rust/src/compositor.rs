use sdl2::{pixels::Color, render::Canvas, video::Window, Sdl};

pub struct Compositor {
    canvas: Canvas<Window>,
    color: u8,
}

impl Compositor {
    pub fn new(sdl_context: &Sdl) -> Self {
        let video_subsystem = sdl_context.video().unwrap();

        let window = video_subsystem
            .window("Revyv (Rust)", 800, 600)
            .position_centered()
            .build()
            .unwrap();

        let mut canvas = window.into_canvas().build().unwrap();
        canvas.set_draw_color(Color::RGB(0, 255, 255));
        canvas.clear();
        canvas.present();

        Self { canvas, color: 0 }
    }

    pub fn compose(&mut self) {
        self.color = (self.color + 1) % 255;
        self.canvas
            .set_draw_color(Color::RGB(self.color, 64, 255 - self.color));
        self.canvas.clear();
        self.canvas.present();
    }
}
