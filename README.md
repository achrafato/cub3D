# Cub3D - Raycasting Game Engine

A 3D game engine inspired by Wolfenstein 3D, using MLX42 library and raycasting techniques.

## 🎮 Requirements

### MLX42 Dependencies (MacOS)
```bash
# Using brew
brew update
brew install glfw
brew install cmake

# Clone MLX42
git clone https://github.com/codam-coding-college/MLX42.git
cd MLX42
cmake -B build
cmake --build build -j4
```

## 🖼️ Features

- Textured walls with famous paintings:
  - Mona Lisa
  - The Starry Night
  - The Scream
  - Sunflowers
  - Girl with a Pearl Earring
  - The Tower of Babel
  - Wheat Field
  - Sunshine

- Smooth movement and rotation
- Collision detection
- Minimap display
- Textured rendering

## 📁 Project Structure

```
.
├── gnl/                    # Get Next Line implementation
│   ├── get_next_line.c
│   ├── get_next_line_utils.c
│   ├── libft.c
│   └── linked_list.c
├── maps/                   # Game maps
│   ├── map.cub
│   ├── map1.cub
│   └── map2.cub
├── parsing/                # Map parsing and validation
│   ├── check_map.c
│   ├── direction.c
│   ├── extention.c
│   ├── open_img.c
│   └── parsing.c
├── textures/              # Wall textures
│   ├── Mona_Lisa.png
│   ├── Sunflowers.png
│   ├── the_starry_night.png
│   └── [other textures]
└── utils/                 # Utility functions
    ├── utils_1.c
    └── [other utils]
```

## 🗺️ Map Format

Maps use `.cub` extension with the following format:
```
NO ./path_to_north_texture
SO ./path_to_south_texture
WE ./path_to_west_texture
EA ./path_to_east_texture

F R,G,B    # Floor color
C R,G,B    # Ceiling color

111111
100101
101001
1000N1     # N indicates player position and direction
111111
```

Map elements:
- `0`: Empty space
- `1`: Wall
- `N/S/E/W`: Player starting position and direction

## 🛠️ Compilation & Usage

### Building
```bash
make        # Compile the program
make clean  # Remove object files
make fclean # Remove object files and executable
make re     # Recompile
```

### Running
```bash
./cub3D maps/map.cub
```

## 🎮 Controls

- `W/S`: Move forward/backward
- `A/D`: Strafe left/right
- `←/→`: Rotate camera
- `ESC`: Exit game


## ⚠️ Error Handling

- Invalid map format
- Missing textures
- Invalid file extension
- Unclosed maps
- Invalid colors
- Memory management
- Missing player position
- Multiple player positions

## 🔍 Technical Implementation

### Raycasting
- DDA (Digital Differential Analysis) algorithm
- Perpendicular distance calculation
- Texture mapping
- Wall height calculation

### Performance Optimizations
- Efficient texture loading
- Frame rate management
- Memory management
- Collision optimization

## 🧪 Testing

Test maps are provided in the `maps/` directory:
- `map.cub`: Basic layout
- `map1.cub`: Complex layout
- `map2.cub`: Advanced features

#
![game show](https://github.com/user-attachments/assets/9f8212ad-e542-4c0e-b5c6-1d40015faeec)

#

## 📜 License

This project is part of the 42 curriculum and is provided as-is.
