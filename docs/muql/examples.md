## Ejemplos de MuQL

**Filtros por categoría**

```txt
performer: "Angel Olsen"
artist: "Geordie Greep"
band: "Black Midi"
album: "Odyssey and Oracle"
song: "Opus"
genre: "Art Pop"
member: "Steven Wilson"
path: "Music/Prog"
track: 3
track: 1 => 5
```

**Temporales**

```txt
from: 1990
to: 2025
year: 1990 => 2025
year: 2010 =>
year: => 2000
year: 2020
year: 1990 => 1999 or 2010 => 2015
```

**Apariencia**

```txt
similar: song like "Black"
similar: performer like "Phoebe"
```

**Lógica**

```txt
performer: "Angel Olsen" and album: "All Mirrors"
performer: "Angel Olsen" not album: "Big Time"
performer: "Angel Olsen" or "Sharon Van Etten"
performer: "Phoebe Bridgers" or performer: "The National"
(performer: "Angel Olsen" or "Sharon Van Etten") and not album: "Big Time"
member: "Steven Wilson" and not band: "Porcupine Tree"
not year: 1990 => 1999
```

**Orden**

```txt
sort: asc by song
sort: desc by year
sort: by album
album: "All Mirrors" sort: asc by album
```