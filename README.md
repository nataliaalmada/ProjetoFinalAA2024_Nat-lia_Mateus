# ProjetoFinal de Análise de Algoritmos (DCC606 - 2024) - Problema do Clique
## Integrantes
- Natalia Almada e Matheus Melo

## Descrição do Projeto
### Análise e descrição do  artigo - Finding All Maximal Connected s-Cliques in Social Networks,
* Disponível em: https://openproceedings.org/2018/conf/edbt/paper-28.pdf
  
### Implementação do Algoritmo do clique/Algoritmo guloso

* Implemente um algoritmo guloso para o problema do Clique;
* Dataset disponível em: (https://www.kaggle.com/datasets/thoughtvector/customer-support-on-twitter)
* Em seguida, defina conjuntos que deverão ser análisado como cliques, para identificar a relação/conexão entre os tweets;
* Pesquise e adote um benchmark de grafos para uma avaliação experimental;
* Apresente uma análise sobre os resultados encontrados com os algoritmos.
### Relatório: 
https://github.com/nataliaalmada/ProjetoFinalAA2024_Natalia_Matheus/blob/main/Relat%C3%B3rio%20Natalia%20e%20Matheus%20Formato%20IEEE.pdf
  
## Cronograma
| Dias           | Atividade                                             | Meta                            | Status    |
|----------------|-------------------------------------------------------|----------------------------------|-----------|
| 11-12/09/2024  | Análise do artigo e estudo do problema do Clique       | Entendimento completo do problema | Feito     |
| 13-15/09/2024  | Implementação do algoritmo guloso e envio para o GitHub com o README | Protótipo funcional do algoritmo | Feito   |
| 16-17/09/2024  | Integração do dataset do Kaggle e definição dos cliques + pull no GitHub | Dados prontos para análise       | Feito   |
| 18-19/09/2024  | Pesquisa e adoção de benchmark de grafos               | Benchmark escolhido e configurado | Feito   |
| 20-21/09/2024  | Avaliação experimental e coleta de resultados          | Resultados obtidos               | Feito |
| 22/09/2024     | Análise e documentação dos resultados                  | Relatório final                  | Feito   |



## Conteúdo
A apresentação do nosso grupo contempla o seguintes tópicos acerca do algoritmo `Problema do Clique`:
https://github.com/nataliaalmada/ProjetoFinalAA2024_Natalia_Matheus/blob/main/Semin%C3%A1rio%20an%C3%A1lise%20de%20Algoritmos-Clique-1.pdf
- Custo e complexidade;
- Código da implementação em C();
- Experimentação da execução do algoritmo com diferentes entradas;
    - Benchmark:https://iridia.ulb.ac.be/~fmascia/maximum_clique/
- Gráfico de linha com quantidade de vertices de cada resultado e
- Tempo de execução;
    - Algoritmo de plot do gráfico

##  Custo e Complexidade

-O(n2)


## Resultados

Conseguimos observar que o `Problema do Clique` possui uma complexidade de O(n2) para seus piores casos  
<div align="center">

### Atualizações após Apresentação
A pedido do professor, gráficos gerados: 

## Gráficos de Desempenho

### Gráfico 1 - Tempo de execução para cada teste
![Gráfico 1 - Tempo de execução para cada teste](https://github.com/nataliaalmada/ProjetoFinalAA2024_Natalia_Matheus/blob/main/mediaGraficosBenchmark-artefatos/Grafico%201.jpeg)

O primeiro gráfico compara o tamanho do clique máximo encontrado pelo seu algoritmo em cada teste com a melhor solução conhecida (do site Iridia). Observa-se que, em todos os testes, o algoritmo encontra um clique de tamanho menor que o ótimo conhecido, mas há uma variação considerável entre os testes. No Teste 1, por exemplo, o algoritmo encontra 26 cliques, enquanto a solução ótima tem 34. No Teste 7, o algoritmo se aproxima mais, encontrando 39 cliques, quando o ótimo é 55. Essa diferença destaca que, embora o algoritmo guloso forneça resultados rapidamente, ele tende a não encontrar o melhor clique possível em grafos mais complexos.

### Gráfico 2 - Precisão do clique encontrado vs melhor solução
![Gráfico 2 - Precisão do clique encontrado vs melhor solução](https://github.com/nataliaalmada/ProjetoFinalAA2024_Natalia_Matheus/blob/main/mediaGraficosBenchmark-artefatos/Grafico%202.jpeg)

Este gráfico ilustra a precisão do algoritmo em cada teste, calculada como a porcentagem do clique máximo encontrado em relação à melhor solução conhecida. A linha vermelha tracejada mostra a precisão média, que gira em torno de 67,23%. Notamos que a precisão varia bastante entre os testes. Por exemplo, no Teste 3, a precisão é baixa (66,67%) em comparação com o ótimo, enquanto no Teste 6, a precisão é de cerca de 68,18%, que é relativamente alta. Isso sugere que o algoritmo pode ser mais eficiente em alguns tipos de grafos, enquanto em outros sua performance é limitada.

### Gráfico 3 - Clique máximo encontrado vs melhor solução conhecida
![Gráfico 3 - Clique máximo encontrado vs melhor solução conhecida](https://github.com/nataliaalmada/ProjetoFinalAA2024_Natalia_Matheus/blob/main/mediaGraficosBenchmark-artefatos/Grafico%203.jpeg)
 O último gráfico apresenta o tempo de execução do algoritmo em cada teste, com a linha vermelha tracejada representando o tempo médio de 0,000796 segundos. É notável que o tempo de execução aumenta conforme a complexidade do grafo. Por exemplo, o Teste 5, que envolve um grafo maior (800 nós e 208.166 arestas), apresenta o maior tempo de execução (0,004152 segundos). Isso evidencia a correlação entre o tamanho e a densidade do grafo com o tempo necessário para encontrar o clique máximo. Em contraste, para grafos menores, como no Teste 1, o tempo de execução é significativamente menor (0,000072 segundos).



## Conclusão
A análise dos gráficos demonstra que o algoritmo guloso, embora rápido, apresenta limitações quanto à precisão na busca pelo clique máximo em grafos mais complexos. O tempo de execução é relativamente baixo para a maioria dos testes, mas aumenta com a complexidade do grafo. Essa análise indica que o algoritmo é eficiente em tempo, mas pode ser aprimorado para aumentar a precisão nos cliques encontrados.

## Objetivos

- [X] Análise Do Artigo;
- [X] Custo e Complexidade;
- [X] Código em C do algoritmo proposto;
- [X] Experimentação com a execução do algoritmo com diferentes entradas e coleta de tempo de execução;
- [X] Gráfico de linha com o tempo de execução em relação a cada entrada e análise da tendência de comportamento assintótico;
- [X] Relatório do Projeto em formato de Artigo;
- [X] Apresentar o algoritmo, mostrando sua eficiência, em termos de complexidade.

