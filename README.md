<div align="center">
  <a href="https://github.com/tucozz/SpotFES">
    <img src="img/logo.png" alt="Logo" width="160" height="160">
  </a>

  <h3 align="center">SpotFES</h3>
</div>

## Sobre

SpotFES foi o primeiro trabalho desenvolvido ao longo da disciplina de Programação II, ministrada pelo professor Vinícius.

Com esse programa você pode encontrar músicas, criar playlists, receber recomendações e exportar relatórios dos seus sons e cantores favoritos.

## Começando

### Pré-requisitos

- Linux (sem suporte pro windows, sra. microsoft)
- [GNU Compiler Collection](https://gcc.gnu.org/)

### Instalando

1. Clone o repositório

    ```sh
    git clone https://github.com/tucozz/SpotFES.git
    ```

2. Dirija-se ao seu diretório

    ```sh
    cd SpotFES/
    ```

3. Compile o código-fonte

    ```sh
    make
    ```

### Usando

O executável precisa dos caminhos para dois arquivos csv com a fonte para as músicas e artistas, nessa ordem.

Esses arquivos podem ser adquiridos por [aqui](https://www.kaggle.com/datasets/yamaerenay/spotify-dataset-19212020-600k-tracks).

```sh
./main data/tracks.csv data/artists.csv
```

## Suporte

Esse programa não funciona em ambientes não-POSIX e pode até mesmo não funcionar em sistemas não-Linux.

Isso se deve ao fato de usar APIs que são extenções do POSIX e não fazem parte do padrão C.

## Licença

Licenciado sob [Unlicense](./LICENSE).
