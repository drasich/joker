#![feature(append)]

extern crate pkg_config;
extern crate gcc;


use std::env;
use std::path::PathBuf;

fn main() {
    let mut paths  = Vec::new();
    if let Ok(ref mut info) = pkg_config::find_library("elementary") {
        //build_elementary_key(&info.include_paths);
        paths.append(&mut info.include_paths);
    }
    if let Ok(ref mut info) = pkg_config::find_library("ecore-x") {
        paths.append(&mut info.include_paths);
    }
    build_elementary_key(&paths);
}

fn build_elementary_key(include_paths: &[PathBuf]) {
    let mut config = gcc::Config::new();

    for path in include_paths {
        config.include(path);
    }

    config.file("src/action.c")
        .file("src/command.c")
        .file("src/glview.c")
        .file("src/list.c")
        .file("src/panel.c")
        .file("src/property.c")
        .file("src/property_list.c")
        .file("src/tree.c")
        .file("src/window.c")
        .compile("libjoker.a");
}

