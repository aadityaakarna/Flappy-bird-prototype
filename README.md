
This is a simple Flappy Bird clone developed using **SFML** (Simple and Fast Multimedia Library). The game includes basic mechanics like gravity, bird flapping, pipes, scoring, and a game-over screen.

## Prerequisites

To compile and run this project on macOS using **Xcode**, you need to have the following installed:

1. **Homebrew** (to install SFML):
   - Install Homebrew using this command in Terminal:
     ```bash
     /bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"
     ```

2. **SFML**:
   - Install SFML via Homebrew:
     ```bash
     brew install sfml
     ```

3. **Xcode** (Download from the Mac App Store):
   - Ensure you have the latest version of Xcode installed.

## Setting up the Project in Xcode

### 1. Create a New Xcode Project
- Open **Xcode**, and create a new project.
- Choose **macOS > Command Line Tool**.
- Set the project name and details.
- Choose **C++** as the language.

### 2. Link SFML Libraries
- Go to **Project Settings** and select your target.
- Under **Build Settings**, find **Search Paths**.
  - Add `/usr/local/include` to **Header Search Paths**.
  - Add `/usr/local/lib` to **Library Search Paths**.

- Under **Build Phases**, expand **Link Binary With Libraries**, and click the "+" button to add the SFML libraries:
  - Add the following frameworks (located in `/usr/local/lib`):
    - `libsfml-graphics.dylib`
    - `libsfml-window.dylib`
    - `libsfml-system.dylib`

### 3. Add SFML Frameworks to the Runpath
- In **Build Settings**, find the **Runpath Search Paths** and add:
  ```
  /usr/local/lib
  ```

### 4. Copy SFML Libraries to Executable Folder
- To ensure SFML libraries are accessible when running your app, you can copy the `.dylib` files into your build folder:
  - Go to **Build Phases**.
  - Add a new **Copy Files** phase.
  - Set the **Destination** to `Executable Folder`.
  - Add all required `.dylib` files from `/usr/local/lib`.

### 5. Set Working Directory
- In **Xcode**, select **Edit Scheme**.
- Under the **Run** option, set the **Working Directory** to the folder containing your assets (e.g., textures like `gameOver.jpg` and `back.jpeg`).

### 6. Compile and Run
- Now you should be able to build and run the project within Xcode.

## Game Controls
- Press `Spacebar` to flap the bird and avoid the pipes.
- The game will end if the bird collides with a pipe or the screen boundaries.
- A high score is saved to `highscore.txt` after each game session.

## Assets
- The game uses two image files:
  - `gameOver.jpg` for the game over screen.
  - `back.jpeg` for the background.
  
Ensure these assets are stored in the appropriate directory (`./accest/`) as referenced in the source code.
Here’s a `README.md` file for compiling and running your SFML project on **Windows** using Visual Studio:


Before running the project on Windows, ensure the following tools are installed:

1. **Visual Studio** (2019 or newer):
   - Download and install from the [Visual Studio website](https://visualstudio.microsoft.com/).
   - Make sure to install the **Desktop development with C++** workload.

2. **SFML Library**:
   - Download the SFML library from the official [SFML website](https://www.sfml-dev.org/download.php).
   - Choose the version compatible with your Visual Studio version (e.g., Visual C++ 15 (2017) - 32-bit or 64-bit).
   - Extract the downloaded files to a convenient location (e.g., `C:\SFML`).

## Setting up the Project in Visual Studio

### 1. Create a New Visual Studio Project
- Open **Visual Studio**, and create a new **Console App** project in C++.
- Set the project name and location.

### 2. Link SFML Libraries to the Project
1. **Configure SFML in Visual Studio**:
   - Right-click your project in **Solution Explorer** and select **Properties**.

2. **C/C++ → General → Additional Include Directories**:
   - Add the path to the `SFML/include` folder (e.g., `C:\SFML\include`).

3. **Linker → General → Additional Library Directories**:
   - Add the path to the `SFML/lib` folder (e.g., `C:\SFML\lib`).

4. **Linker → Input → Additional Dependencies**:
   Add the following dependencies:
   - `sfml-graphics.lib`
   - `sfml-window.lib`
   - `sfml-system.lib`

5. If you are running the project in **Debug mode**, use the debug versions of the SFML libraries by adding:
   - `sfml-graphics-d.lib`
   - `sfml-window-d.lib`
   - `sfml-system-d.lib`

### 3. Copy SFML DLL Files
- After setting up the project, ensure the `.dll` files from the `SFML/bin` folder (e.g., `sfml-graphics-2.dll`, `sfml-window-2.dll`, `sfml-system-2.dll`) are copied to the output directory of your project (e.g., `Debug/` or `Release/`).

### 4. Set Working Directory for Assets
- Place your assets like `gameOver.jpg` and `back.jpeg` in a folder called `assets` in your project directory.
- To configure the working directory in Visual Studio:
  - Right-click the project and go to **Properties → Debugging**.
  - Set the **Working Directory** to the location of your `assets` folder.

### 5. Compile and Run
- Build the project by clicking **Build** → **Build Solution** (or press `Ctrl + Shift + B`).
- Run the game by pressing `F5` or clicking **Debug** → **Start Debugging**.

## Game Controls
- Press `Spacebar` to make the bird flap and avoid the pipes.
- The game ends if the bird hits a pipe or the screen boundaries.
- The highest score is saved to a file called `highscore.txt`.

## Assets
Ensure you have the following assets in the `assets` directory:
- `gameOver.jpg` (for the game over screen)
- `back.jpeg` (for the game background)

Make sure the image paths in the code match the location of these files.
