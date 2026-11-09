<p align="center">
  <a href="https://github.com/evanrock520-ciencias/8-Track/actions/workflows/ci.yml">
    <img src="https://github.com/evanrock520-ciencias/8-Track/actions/workflows/ci.yml/badge.svg" alt="CI State">
  </a>
  <img src="https://img.shields.io/badge/C%2B%2B-20-00599C?logo=cplusplus&logoColor=white" alt="C++20">
  <img src="https://img.shields.io/badge/Qt-6-41CD52?logo=qt&logoColor=white" alt="Qt 6">
  <img src="https://img.shields.io/badge/CMake-3.25%2B-064F8C?logo=cmake&logoColor=white" alt="CMake">
</p>

---

# 8-Track

**8-Track** es un gestor de música local desarrollado en **C++ 20** y **Qt 6**
para la plataforma **Linux**.

<img width="1280" height="720" alt="Image" src="https://github.com/user-attachments/assets/ec4a033a-91de-4c6a-a185-3a2ad05a5403" />

## Features

- Escaneo de archivos **mp3**.
- Exploración de artistas, álbumes y canciones.
- Búsquedas avanzadas mediante [**MuQL**](/docs/muql/examples.md).
- Edición de metadatos (en la base de datos).
- Reproducción de audio.

## Requisitos

- Compilador compatible con **C++20**, como **GCC** o **Clang**.
- **CMake 3.25** o superior.
- **Qt 6.8** o superior, con los módulos:
  - Qt Quick.
  - Qt SQL.
  - Qt Multimedia.

### Recomendaciones

Para compilar con el preset de **release** es necesario instalar:

- **Ninja**
- **Ccache**
- **Mold**

<details>
  <summary>Fedora</summary>

```bash
sudo dnf install ninja-build mold ccache
```

</details>

### Dependencias

Además, varias dependencias se incluyen mediante **Fetch Content**.

#### Globales

| Biblioteca | Versión |
| ---------- | ------- |
| Taglib     | 2.3.2   |
| Picosha2   | 1.0.1   |

#### CLI

| Biblioteca | Versión |
| ---------- | ------- |
| Tabulate   | 2.0     |
| Argparse   | 3.2     |
| Indicators | 2.3     |

## Compilación

### Preset Release

```bash
git clone https://github.com/evanrock520-ciencias/8-Track.git
cd 8-Track
cmake -S . --preset release
cmake --build --preset release
```

### Normal

```
git clone https://github.com/evanrock520-ciencias/8-Track.git
cd 8-Track
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build
```

## Terminal

### Quickstart

**8-track** proporciona una CLI para realizar operaciones elementales como:

### Scan

Escanea tu biblioteca musical.

```
./build/release/track8-cli --scan "$HOME/Music"
```

<img src="https://vhs.charm.sh/vhs-4WmZcsXk5aX3XTE6WQLEMy.gif" alt="Scan">

### Query

Realiza potentes consultas utilizando **MuQL**.

```bash
./build/release/track8-cli --query 'song: "Black"'
```

<img src="https://vhs.charm.sh/vhs-xkjTYZAKLWxggVLjX2x8q.gif" alt="List">

## Pruebas

Para ejecutar las pruebas unitarias también se proporciona **Google Test**.

### Release

```bash
ctest --test-dir build/release --output-on-failure
```

### Normal

```bash
ctest --test-dir build --output-on-failure
```

## Documentación

La documentación del proyecto se puede encontrar en [8-track](https://evanrock520-ciencias.github.io/8-Track/).

## Licencia

Este proyecto se encuentra bajo la licencia [GPL-3](LICENSE).
