# Spectra

A Work in progress systems programming language.

## Table of Contents

- [Current State](#current-state)
- [Future Goals](#future-goals)
- [Installation](#installation)
- [Usage](#usage)
- [Contributing](#contributing)
- [License](#license)

## Current State

Currently there is no way to compile and run Spectra source code.

## Future Goals

Abiliity to declare variables, functions, data structures.
Abiliity to run source code.
Aibility to output compiled source code to an executable program.

## Installation

```
git clone https://github.com/ChaseSunstrom/Spectra.git
cd Spectra
```

Then run the CMBR.sh build script in the project root directory with the file you want to run 
```
./CMBR.sh (path to your .spct file)
```

## Usage

Currently there is no way to run Spectra source code, however, what Spectra code might look like:
```rust

use std::io;

void main () {
  my_class foo = my_name_space::my_class::default();

  //use "use space (your_namespace)" to not have to declare the namespace of the type/object you are trying to use
  //works for the current scope
  use space my_namespace;
  my_class bar = my_class::default();
}

space my_name_space {

  class my_class {
    priv int _my_int;
    priv string _my_string;

    //will create an object with all data types to their most minimal value
    pub fn default;

    pub fn void my_function() {
      io::print("Hello, World!");
    }
  }
}
```

## Contributing

Anyone can contribute through pull requests!
