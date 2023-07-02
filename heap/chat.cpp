#include <iostream>
#include <queue>
#include <vector>

// Estrutura para representar um cliente
struct Cliente {
    int quantidadeItens;
    int tempoAtendimento;

    // Construtor
    Cliente(int quantidadeItens, int tempoAtendimento)
        : quantidadeItens(quantidadeItens), tempoAtendimento(tempoAtendimento) {}
};

// Função para calcular o tempo mínimo de atendimento
int calcularTempoMinimoAtendimento(int quantidadeClientes, std::vector<int>& quantidadeItens, int quantidadeCaixas, std::vector<int>& temposCaixas) {
    // Fila de prioridade para os clientes
    std::priority_queue<Cliente, std::vector<Cliente>, std::greater<Cliente>> filaPrioridade;

    // Adiciona os clientes à fila de prioridade
    for (int i = 0; i < quantidadeClientes; i++) {
        filaPrioridade.push(Cliente(quantidadeItens[i], temposCaixas[0]));
    }

    // Distribui os clientes nas caixas
    for (int caixa = 1; caixa <= quantidadeCaixas; caixa++) {
        for (int i = 0; i < quantidadeClientes / quantidadeCaixas; i++) {
            Cliente cliente = filaPrioridade.top();
            filaPrioridade.pop();
            cliente.tempoAtendimento += temposCaixas[caixa - 1];
            filaPrioridade.push(cliente);
        }
    }

    // Encontra o tempo máximo de atendimento entre todos os clientes
    int tempoMaximo = 0;
    while (!filaPrioridade.empty()) {
        tempoMaximo = std::max(tempoMaximo, filaPrioridade.top().tempoAtendimento);
        filaPrioridade.pop();
    }

    return tempoMaximo;
}

int main() {
    int quantidadeClientes = 3;
    std::vector<int> quantidadeItens = {10, 5, 3};
    int quantidadeCaixas = 2;
    std::vector<int> temposCaixas = {1,2};

    int tempoMinimo = calcularTempoMinimoAtendimento(quantidadeClientes, quantidadeItens, quantidadeCaixas, temposCaixas);

    std::cout << "Tempo mínimo de atendimento: " << tempoMinimo << " unidades de tempo\n";

    return 0;
}
