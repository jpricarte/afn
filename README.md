# Automaton Friendly Notation (.afn)

Automaton Friendly Notation é uma notação criada para montar um autômato de forma legível,
tanto para quem o modela, como para o computador.

## EXTENSÃO

Usaremos a extensão .afn (automaton friendly notation) para os arquivos de texto que utilizem a notação.

##DECLARAÇÃO DE ESCOPO

O automato começa após uma linha onde está escrito apenas `start_automaton`
e termina em uma linha escrito `end_automaton`.


## COMANDOS

### Estado

Para declarar um estado, você usa o comando

```
    $ nome_estado : tipo
```

tipos de estados:

- `initial`
- `final`
- `initial,final`
- `none`

#### Observações

- Apenas o primeiro estado será declarado como inicial. Se declarar mais de um como
inicial, um dos estados deixará de ser do tipo `initial`, dependendo de como for programado o interpretador. 

- Estados que não estejam
nessa lista serão salvos como none.

- O tipo `initial,final` cria um estado inicial e final ao mesmo tempo.

### Transição (aresta)

Para declarar uma transição, você usa o comando

```
    - char (ou string) : novo_estado
```

**OBS**: o caracter ':' não pode ser utilizado em string

### Declarar Transições

Para declarar transições após a declaração, você pode declarar novas transições usando:

```
& nome_estado
    - char (ou string) : novo_estado
    [...]
```

Apesar do interpretador modelo aceitar declarações de transições logo abaixo da declaração de estados,
não recomendo o uso dessa, porque dessa forma poderão ocorrer erros de ponteiro.

### Comentários

Para comentar dentro do escopo, usamos o comando

```
    # comentario
```

## SINTAXE

Recomendo o uso de caracteres ASCII dentro do escopo do texto, para garantir que qualquer
interpretador irá conseguir ler seu automato.

Os caracteres de transição podem ser todos os caracteres visiveis - { ' ', '\t', '\n' }.
Isso inclui os caracteres de controle. Porém, como dito antes, se você quiser usar ':' como
caracter de transição, você deve declará-lo separadamente dos demais.

Cada linha deve ter **SOMENTE UM** comando, comentarios **NÃO** podem ser escritos
na mesma linha que outros comandos.

Identações ajudam a modelar o programador a modelar e visualizar seu autômato,
mas elas serão ignoradas na leitura pelo computador.

Tudo que estiver escrito fora do escopo definido entre os comandos de inicio e fim
serão ignorados na leitura e considerados comentários.

Para evitar erros de ponteiros,
**todos os estados devem ser declarados antes de declarar as transições**.
As transições no interpretador modelo só apontam para estados pré declarados.

Ao usar uma string nas transições, cada caracter da string será gerará uma nova transição
para o mesmo estado.

## Interpretador Modelo

O interpretador modelo foi criado em C++. Ele foi inscrito de forma que satisfaça todas
as especificações acima. Porém, ele atualmente verifica *apenas*
Autômatos Finitos.

A linguagem, por estar em fase de desenvolvimento, tem garantia de funcionamento para
*autômatos finitos*. nas próximas versões suportarão outros tipos de autômatos.

### Biblioteca
A biblioteca Automaton contém as classes criadas para gerar o interpretador.
O arquivo test_file_pt.cpp contém um teste simples para vê-lo funcionando.

## Exemplos

A pasta Examples contém o arquivo teste_file_pt.cpp pré-compilado, e dois
autômatos.

### automaton.afn

Autômato para linguagem:

```
L = { w | w contenha a sub-palavra 'ab' ou # par de 'a' ou sufixo 'b' apos par de 'aa' }
```

Criado para demonstrar o estado `initial,final` e 2 estados finais

### hour_checker.afn

Autômato para linguagem:

```
L = { w | w está é um horário valido num dos formatos descritos abaixo }
```

- **HH**:**MM**
- **HH**h**MM**
- **HH**H**MM**
- **HH**-**MM**

### non_det.afn

Autômato Finito Não Deterministico para linguagem:

```
L = { w | w contenha a subpalavra aa ou bb }
```
