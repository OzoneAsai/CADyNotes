# CADyNotes

Rustバックエンド + Qt UI の最小構成サンプルです。将来の CAD 風 Note アプリ開発に向けた土台として、まずは **Mac / Windows / Linux** で動かせる構成を作っています。

## 構成

- `rust-backend/`: Rust 製バックエンド（JSONを標準出力）
- `qt-ui/`: Qt Widgets 製デスクトップUI（Rustプロセスを起動して表示）

## 1. Rustバックエンドをビルド

```bash
cd rust-backend
cargo build
```

動作確認:

```bash
cargo run -- hello
```

## 2. Qt UI をビルド

Qt6（Widgets）が必要です。

```bash
cd qt-ui
cmake -S . -B build
cmake --build build
```

## 3. 実行

### Linux/macOS

```bash
cd qt-ui/build
./CADyNotesQt
```

### Windows (PowerShell)

```powershell
cd qt-ui\build
.\CADyNotesQt.exe
```

UIの「Run Rust backend」ボタンを押すと、Rustバックエンドを実行してメッセージを表示します。

## 補足（バックエンドパス）

既定では以下の相対パスを使います。

- Windows: `..\rust-backend\target\debug\cadynotes-backend.exe`
- Linux/macOS: `../rust-backend/target/debug/cadynotes-backend`

必要なら環境変数 `CADYNOTES_BACKEND_BIN` で実行ファイルの絶対/相対パスを指定できます。
