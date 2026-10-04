from swarm import Swarm, Agent
from openai import OpenAI

# 1. Configurar o cliente com a API Key da Moonshot e a URL base deles
kimi_client = OpenAI(
    api_key="sk-o4T0DbIHtkSD1UxGxQyeOn2WfQEs7TFpvoVhdqa2k7hfCfQ9",
    base_url="https://api.moonshot.cn/v1"
)

# 2. Inicializar o Swarm com o cliente modificado
client = Swarm(client=kimi_client)

# 3. Criar uma função de ferramenta
def dar_conselho_jogo():
    return "Mantenha o escopo do seu GDD enxuto e direto ao ponto!"

# 4. Criar o agente utilizando o modelo do Kimi
agente_desenvolvedor = Agent(
    name="Assistente GDD",
    instructions="Você é um assistente técnico especialista em design de jogos.",
    model="moonshot-v1-8k",
    functions=[dar_conselho_jogo],
)

# 5. Executar o fluxo
resposta = client.run(
    agent=agente_desenvolvedor,
    messages=[{"role": "user", "content": "Olá! Preciso de uma dica para o projeto do jogo."}],
)

print(resposta.messages[-1]["content"])
