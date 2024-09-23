import pandas as pd
import random

# Carregar o arquivo CSV
df = pd.read_csv('twcs.csv')

# Exibir os primeiros registros do DataFrame
print(df.head())

# Verificar o total de tweets
print(f"Total de tweets: {len(df)}")

# Dicionário para armazenar as relações entre tweets
relations = {}

# Processar cada tweet
for index, row in df.iterrows():
    if index % 1000 == 0:  # Exibir a cada 1000 tweets
        print(f"Processando tweet {index}...")

    # Verificar se há resposta a outros tweets
    response_tweet_ids = row['response_tweet_id']
    if pd.notna(response_tweet_ids):
        response_ids = str(response_tweet_ids).split(',')
        for response_id in response_ids:
            response_id = response_id.strip()
            if row['tweet_id'] not in relations:
                relations[row['tweet_id']] = []
            relations[row['tweet_id']].append(response_id)

# Limitar o número de nós (tweets) e arestas (respostas)
MAX_NODES = 500
MAX_EDGES = 112332

# Selecionar no máximo 500 nós (tweets)
limited_nodes = random.sample(list(relations.keys()), min(MAX_NODES, len(relations)))

# Selecionar no máximo 112332 arestas
limited_relations = {}
total_edges = 0
for tweet_id in limited_nodes:
    if total_edges >= MAX_EDGES:
        break
    responses = relations[tweet_id]
    # Adicionar respostas até atingir o limite de arestas
    for response_id in responses:
        if total_edges < MAX_EDGES:
            if tweet_id not in limited_relations:
                limited_relations[tweet_id] = []
            limited_relations[tweet_id].append(response_id)
            total_edges += 1
        else:
            break

# Mapeamento de IDs de tweets para um intervalo de 1 a 500
id_mapping = {old_id: new_id for new_id, old_id in enumerate(limited_nodes, start=1)}

# Salvar as relações em um arquivo DIMACS
with open('relations.dimacs', 'w') as f:
    f.write(f"p edge {len(limited_relations)} {total_edges}\n")
    for tweet_id, responses in limited_relations.items():
        new_tweet_id = id_mapping[tweet_id]
        for response_id in responses:
            if response_id in id_mapping:
                new_response_id = id_mapping[response_id]
                f.write(f"e {new_tweet_id} {new_response_id}\n")

print(f"Relações salvas no arquivo relations.dimacs com {len(limited_relations)} nós e {total_edges} arestas")
