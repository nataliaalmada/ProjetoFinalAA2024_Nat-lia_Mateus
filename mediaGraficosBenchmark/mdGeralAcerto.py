#RODE O COMANDO PYTHON3 mdGeralAcerto.py

import matplotlib.pyplot as plt
import numpy as np

testes = ['Teste 1', 'Teste 2', 'Teste 3', 'Teste 4', 'Teste 5', 'Teste 6', 'Teste 7']
clique_maximo_encontrado = [26, 33, 8, 12, 14, 30, 39] 
melhor_solucao_conhecida = [34, 57, 12, 17, 24, 44, 55]  

tempos = [0.000072, 0.000834, 0.000357, 0.000404, 0.004152, 0.000232, 0.000523]  

precisao = [encontrado / melhor * 100 for encontrado, melhor in zip(clique_maximo_encontrado, melhor_solucao_conhecida)]

media_precisao = np.mean(precisao)
media_tempo = np.mean(tempos)

plt.figure(figsize=(10, 5))

plt.subplot(1, 2, 1)
plt.bar(testes, clique_maximo_encontrado, color='blue', alpha=0.7, label='Clique Máximo Encontrado')
plt.plot(testes, melhor_solucao_conhecida, color='red', marker='o', linestyle='--', label='Melhor Solução Conhecida')
plt.ylabel('Tamanho do Clique')
plt.title('Clique Máximo Encontrado vs Melhor Solução Conhecida')
plt.legend()

plt.subplot(1, 2, 2)
plt.bar(testes, precisao, color='green', alpha=0.7)
plt.axhline(media_precisao, color='red', linestyle='--', label=f'Média de Precisão: {media_precisao:.2f}%')
plt.ylabel('Precisão (%)')
plt.title('Precisão do Clique Encontrado vs Melhor Solução')
plt.legend()

plt.tight_layout()
plt.show()

plt.figure(figsize=(8, 5))
plt.bar(testes, tempos, color='orange', alpha=0.7)
plt.axhline(media_tempo, color='red', linestyle='--', label=f'Tempo Médio: {media_tempo:.6f} s')
plt.ylabel('Tempo (segundos)')
plt.title('Tempo de Execução para Cada Teste')
plt.legend()

plt.tight_layout()
plt.show()



""""

Clique Máximo Encontrado vs Melhor Solução Conhecida:

O gráfico à esquerda mostra o tamanho máximo do clique encontrado pelo seu algoritmo em cada teste, comparado à melhor solução conhecida do site Iridia.

Precisão em porcentgem (%):

O gráfico à direita exibe a porcentagem de precisão dos cliques encontrados pelo seu algoritmo em relação à melhor solução conhecida. A linha tracejada vermelha indica a média de precisão em todos os testes, que é de cerca de 67,23%.

Tempo de Execução de Cada Teste:

O segundo gráfico mostra o tempo gasto para cada teste, com a linha tracejada vermelha representando o tempo médio em todos os testes, aproximadamente 0,000796 segundos.
    
"""