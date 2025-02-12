# KMeans-Trabalho-Final

Este repositório contém o trabalho final da disciplina de Laboratório de Programação 2024.2 do curso de Ciência da Computação. O projeto implementa o algoritmo de agrupamento K-Means, uma técnica de aprendizado não supervisionado utilizada para particionar um conjunto de dados em K grupos distintos, baseando-se nas características intrínsecas dos dados.

## Compilação e Execução

Para compilar e executar o projeto, siga os seguintes passos:

### 1. Compilação do Projeto

Utilize o `Makefile` para compilar o projeto. No terminal, navegue até o diretório raiz do repositório e execute:

```bash
make all
```

Esse comando irá compilar os arquivos-fonte e gerar os executáveis correspondentes no diretório `bin/`.

### 2. Permissão para Execução do Script

O script `run.sh` facilita a execução das diferentes funcionalidades do projeto. Antes de utilizá-lo, é necessário garantir que ele possui permissão de execução. No terminal, execute:

```bash
chmod +x run.sh
```

### 3. Execução das Funcionalidades

O script `run.sh` aceita diferentes parâmetros para executar funcionalidades específicas:

#### Execução Principal (`main`)

Executa o algoritmo K-Means no conjunto de dados inicial e salva os resultados:

```bash
./run.sh main <k> <maxIterations>
```

Onde:
- `<k>`: Número de centroides desejados.
- `<maxIterations>`: Número máximo de iterações para o algoritmo.

Exemplo:

```bash
./run.sh main 5 100
```

#### Cálculo do Coeficiente Dice (`dice`)

Calcula o coeficiente Dice entre os resultados obtidos e o conjunto de dados alvo:

```bash
./run.sh dice
```

#### Geração de Histogramas (`histogram`)

Gera histogramas dos conjuntos de dados inicial e resultante:

```bash
./run.sh histogram
```

#### Cálculo do Erro Quadrático Médio (SSE) (`sse`)

Calcula o Erro Quadrático Médio dos clusters formados:

```bash
./run.sh sse <maxK> <maxIterations>
```

Onde:
- `<maxK>`: Número máximo de centroides desejados.
- `<maxIterations>`: Número máximo de iterações para o algoritmo.

Exemplo:

```bash
./run.sh sse 5 100
```

**Observação:** Certifique-se de que os caminhos dos diretórios e arquivos mencionados no script `run.sh` estão corretos e que os arquivos necessários estão presentes nos locais especificados.
