use serde::Serialize;
use std::env;

#[derive(Serialize)]
struct BackendResponse {
    app: &'static str,
    version: &'static str,
    message: String,
    args: Vec<String>,
}

fn main() {
    let args: Vec<String> = env::args().skip(1).collect();
    let message = if args.is_empty() {
        "CADyNotes Rust backend is running".to_string()
    } else {
        format!("CADyNotes backend received: {}", args.join(" "))
    };

    let response = BackendResponse {
        app: "CADyNotes",
        version: env!("CARGO_PKG_VERSION"),
        message,
        args,
    };

    println!(
        "{}",
        serde_json::to_string(&response).expect("backend response must be valid JSON")
    );
}
