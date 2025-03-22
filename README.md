# Trabalho 1 - Laboratório de Sistemas Operacionais

### Instalação

O processo de instalação ocorre através da execução do script `t1_install`, responsável 
por compilar e instalar os dois programas do trabalho em sua distribuição Linux. Além disso,
ele adiciona ao seu script `pre-build.sh` linhas necessárias para inicializar os dois
programas no boot da distribuição.

Para executar esse script, altere as variáveis no arquivo `.config` de maneira a 
apontarem para os caminhos **ABSOLUTOS** corretos.

1. `i686-linux-gcc-path` - deve apontar para o executável do compilador cruzado.
2. `target-root-dir` - deve apontar para o diretório raiz da distribuição.
3. `pre-build-path` - deve apontar para o seu arquivo de pré build. O presente
                      tutorial assume o script apontado já está configurado para
                      rodar no boot da distribuição.

Após rodar o script com o arquivo `.config` configurado corretamente, os programas já
estarão instalados e prontos para serem inicializados no boot.

## Créditos

### Trabalho realizado por:

    1. Pedro Mezacasa Muller
    2. Guilherme Melgari Vásquez
    3. Henrique Zapella Rocha

### Professor: 
    Sérgio Johann Filho

### Instituição:
    PUCRS - Escola Politécnica
