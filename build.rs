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
    if let Ok(ref mut cypher) = env::var("DEP_CYPHER_INCLUDE") {
        paths.push(PathBuf::from(&*cypher));
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
        .file("src/common.c")
        .file("src/glview.c")
        .file("src/list.c")
        .file("src/panel.c")
        .file("src/property.c")
        .file("src/property_list.c")
        .file("src/tree.c")
        .file("src/window.c")
        .define("EVAS_GL", None)
        .compile("libjoker.a");

     let out_dir = env::var("OUT_DIR").unwrap();

    println!("cargo:rustc-link-search=native={}", out_dir);
    println!("cargo:rustc-link-lib=static=joker");
    //println!("cargo:include={}/src", env::current_dir().unwrap().display());

}

