# Busca e Ordenação
## Projeto 1
**Professor:** Tadeu Zubaran

## 1. Introdução

Neste projeto, teremos a oportunidade de aplicar os conceitos de busca e ordenação que estudamos em sala de aula em um cenário que simula os desafios que vocês encontrarão no futuro.

Criaremos implementações usando algoritmos de busca e ordenação para organizar uma base de dados contendo informações sobre filmes e cinemas. Durante esse processo, teremos aulas práticas no laboratório.

Na avaliação apresentaremos nossas soluções funcionais ao professor, que fará perguntas para avaliar nossa compreensão detalhada das implementações. Posteriormente compartilharemos nossos projetos com os colegas em forma de um pequeno seminário.

## 2. Definição

O usuário poderá utilizar procurar por filmes ou cinemas.

### No caso de filme, o usuário poderá utilizar os seguintes filtros:

1. Filmes de um ou mais tipos (coluna titleType).
2. Filmes que pertencem a um ou mais gêneros (coluna genres).
3. Filmes com uma duração específica entre um limite inferior e superior em minutos.
4. Filmes lançados em um ano específico ou em um intervalo de anos.

### No caso de cinema, o usuário poderá utilizar os seguintes filtros:

1. Cinemas que contém filmes de um ou mais tipos (coluna titleType).
2. Cinemas que contém filmes que pertencem a um ou mais gêneros (coluna genres).
3. Cinemas que contém filmes com uma duração específica entre um limite inferior e superior em minutos.
4. Cinemas em uma localização de até uma distância definida de um local.
5. Cinemas com preços até um limite superior de unidades monetárias.
6. Cinemas que contém filmes lançados em um ano específico ou em um intervalo de anos.

Em ambos os casos os filtros podem ser combinados livremente pelo usuário utilizando os operadores lógicos "e" ou "ou".

### Exemplos:

- Consultar cinemas que tenham filme de gênero "Documentary" ou "Short", e distância de no máximo 1000 do ponto (20019, 510301), com preço no máximo 15,00.
- Consultar filmes do tipo "tvEpisode" feitos no ano 2004, do gênero Comedy ou Talk-Show.

Os dados dos cinemas e filmes estarão em arquivos disponibilizados. Caso o cinema referencie um código de filme que não existe você deve pegar o filme com o código maior mais próximo do código do filme.

**Importante:** Seu trabalho deve sempre mostrar o tempo utilizado, tanto ao carregar a base de dados, quanto ao mostrar as buscas. É preferível um tempo considerável ao carregar, que ao consultar.

## 3. Entrega

A entrega consiste de 2 componentes:

- Upload do código e apresentação no Google Classroom.
- Apresentação de seminário para os colegas.

A apresentação deve explicar como seu trabalho foi feito e suas decisões de projeto. O aluno deve demonstrar o seu código funcionando durante a apresentação, em exemplos que ilustram as decisões de projeto. A apresentação deve mostrar entendimento do código e das suas decisões de projeto, justificando o que foi feito usando o conteúdo aprendido.

**Trabalhos sem qualquer uma das 2 componentes não serão considerados.**

## 4. Avaliação

### Critérios de avaliação:

- Clareza e corretude do código e da sua explicação.
- Qualidade e explicação das decisões de projeto.
- Código implementado com boas práticas de programação.
- Qualidade de apresentação para os colegas e participação com perguntas nas apresentações dos outros grupos.

**⚠️ Não copie o código. Faça seu próprio código! Plágio receberá nota 0.**
