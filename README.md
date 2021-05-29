# Keisan (計算)

[![latest version](https://img.shields.io/github/v/release/ichiro-its/keisan)](https://github.com/ichiro-its/keisan/releases/)
[![commits since latest version](https://img.shields.io/github/commits-since/ichiro-its/keisan/latest)](https://github.com/ichiro-its/keisan/commits/master)
[![license](https://img.shields.io/github/license/ichiro-its/keisan)](./LICENSE)
[![test status](https://img.shields.io/github/workflow/status/ichiro-its/keisan/Build%20and%20Test?label=test)](https://github.com/ichiro-its/keisan/actions/workflows/build-and-test.yml)

Keisan (計算, calculation) is a [ROS 2](https://docs.ros.org/en/foxy/index.html) package that provides a math equations and algorithms library for a ROS 2 project.

## Features

- Contains number and angle equations like clamp, conversion, map, etc.
- Store and calculate matrixes and vectors.
- Store and do transformation on geometry points.

## Requirement

- This package requires [ROS 2 Foxy Fitzroy](https://docs.ros.org/en/foxy/).

## Installation

### Binary Packages

- See [releases](https://github.com/ichiro-its/keisan/releases) for the latest version of this package.
- Alternatively, this package also available on [ICHIRO ITS Repository](https://repository.ichiro-its.org/) as `ros-foxy-keisan` package.

### Build From Source

- Install colcon as in [this guide](https://colcon.readthedocs.io/en/released/user/installation.html).
- Build the project and source the result.
  ```bash
  $ colcon build
  $ source install/setup.bash
  ```
  > See [this guide](https://docs.ros.org/en/foxy/Tutorials/Workspace/Creating-A-Workspace.html) for more information on how to setup a workspace in ROS 2.

## License

This project is maintained by [ICHIRO ITS](https://ichiro-its.org/) and licensed under the [MIT License](./LICENSE).
