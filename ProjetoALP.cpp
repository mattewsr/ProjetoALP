#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <tuple>

using namespace std;

// Definição de tipo para representar um produto
typedef tuple<string, double, int> Produto;

// Função para adicionar um produto na lista de produtos
void adicionarProduto(vector<Produto>& produtos, const string& nome, double preco, int quantidade) {
    produtos.push_back(make_tuple(nome, preco, quantidade));
}

// Função para remover um produto da lista de produtos
void removerProduto(vector<Produto>& produtos, int indice) {
    produtos.erase(produtos.begin() + indice);
}

// Função para editar um produto ou preço na lista de produtos
void editarProduto(vector<Produto>& produtos, int indice, const string& novoNome, double novoPreco) {
    get<0>(produtos[indice]) = novoNome;
    get<1>(produtos[indice]) = novoPreco;
}

// Função para listar os produtos disponíveis
void listarProdutos(const vector<Produto>& produtos) {
    cout << "Produtos disponíveis:" << endl;
    for (int i = 0; i < produtos.size(); i++) {
        cout << i + 1 << ". " << get<0>(produtos[i]) << " - R$" << fixed << setprecision(2) << get<1>(produtos[i]);
        if (get<2>(produtos[i]) > 0) {
            cout << " (" << get<2>(produtos[i]) << " disponíveis)";
        } else {
            cout << " (esgotado)";
        }
        cout << endl;
    }
    cout << endl;
}

// Função para processar a compra de um produto
void comprarProduto(vector<Produto>& produtos, int indice, double valorInserido, double& faturamento) {
    if (indice >= 0 && indice < produtos.size()) {
        Produto& produto = produtos[indice];
        if (get<2>(produto) > 0 && valorInserido >= get<1>(produto)) {
            get<2>(produto)--;
            double troco = valorInserido - get<1>(produto);
            faturamento += get<1>(produto);
            cout << "Produto comprado: " << get<0>(produto) << endl;
            if (troco > 0) {
                cout << "Troco: R$" << fixed << setprecision(2) << troco << endl;
            }
            cout << endl;
        } else {
            cout << "Produto indisponível ou valor inserido insuficiente." << endl << endl;
        }
    } else {
        cout << "Índice inválido." << endl << endl;
    }
}

// Função para mostrar o potencial de venda de acordo com o estoque restante
void mostrarPotencialVenda(const vector<Produto>& produtos) {
    double potencialVenda = 0.0;
    for (const auto& produto : produtos) {
        potencialVenda += get<1>(produto) * get<2>(produto);
    }
    cout << "Potencial de venda: R$" << fixed << setprecision(2) << potencialVenda << endl;
}

int main() {
    vector<Produto> produtos;

    // Adicionando produtos iniciais
    adicionarProduto(produtos, "Ruffles ", 12.50, 10);
    adicionarProduto(produtos, "Chetos queijo ", 13.50, 10);
    adicionarProduto(produtos, "Chetos parmesão ", 13.50, 10);
    adicionarProduto(produtos, "Doritos ", 15.00, 10);
    adicionarProduto(produtos, "Água com gás ", 5.00, 10);
    adicionarProduto(produtos, "Água sem gás ", 5.00, 10);
    adicionarProduto(produtos, "Coca cola ", 6.00, 10);
    adicionarProduto(produtos, "Coca cola zero ", 6.00, 10);
    adicionarProduto(produtos, "Guaraná antártica ", 6.00, 10);
    adicionarProduto(produtos, "Guaraná antártica zero ", 6.00, 10);
    adicionarProduto(produtos, "Sprite ", 6.00, 10);
    adicionarProduto(produtos, "Sprite zero ", 6.00, 10);
    adicionarProduto(produtos, "Sufleir ", 7.00, 10);
    adicionarProduto(produtos, "Hershey's ao leite ", 7.00, 10);
    adicionarProduto(produtos, "Hershey's amargo", 7.00, 10);
    adicionarProduto(produtos, "Trident hortelã", 5.00, 10);
    adicionarProduto(produtos, "Halls extra forte", 4.00, 10);
    adicionarProduto(produtos, "Coookie balduco ", 6.00, 10);
    adicionarProduto(produtos, "Toddynho ", 5.00, 10);
    adicionarProduto(produtos, "Barra de cereal ", 4.50, 10);

    int modo;
    bool isAdmin = false;
    double faturamento = 0.0;
    string senha;

    do {
        cout << "Selecione o modo:" << endl;
        cout << "1. Modo Cliente" << endl;
        cout << "2. Modo Administrador" << endl;
        cout << "0. Sair" << endl;
        cin >> modo;

        if (modo == 1) {
            listarProdutos(produtos);

            int indice;
            cout << "Digite o índice do produto desejado: ";
            cin >> indice;

            double valorInserido;
            cout << "Digite o valor inserido: ";
            cin >> valorInserido;

            comprarProduto(produtos, indice - 1, valorInserido, faturamento);
        } else if (modo == 2) {
            cout << "Digite a senha: ";
            cin >> senha;

            if (senha == "1234567") {
                isAdmin = true;
                int opcao;

                do {
                    cout << "Selecione uma opção:" << endl;
                    cout << "1. Adicionar produto" << endl;
                    cout << "2. Excluir produto" << endl;
                    cout << "3. Editar produto ou preço" << endl;
                    cout << "4. Listar produtos" << endl;
                    cout << "5. Mostrar potencial de venda" << endl;
                    cout << "0. Voltar" << endl;
                    cin >> opcao;

                    if (opcao == 1) {
                        string nome;
                        double preco;
                        int quantidade;

                        cout << "Digite o nome do produto: ";
                        cin.ignore();
                        getline(cin, nome);

                        cout << "Digite o preço do produto: ";
                        cin >> preco;

                        cout << "Digite a quantidade inicial do produto: ";
                        cin >> quantidade;

                        adicionarProduto(produtos, nome, preco, quantidade);

                        cout << "Produto adicionado com sucesso!" << endl << endl;
                    } else if (opcao == 2) {
                        listarProdutos(produtos);

                        int indice;
                        cout << "Digite o código do produto que deseja excluir: ";
                        cin >> indice;

                        removerProduto(produtos, indice - 1);

                        cout << "Produto excluído com sucesso!" << endl << endl;
                    } else if (opcao == 3) {
                        listarProdutos(produtos);

                        int indice;
                        cout << "Digite o índice do produto que deseja editar: ";
                        cin >> indice;

                        string novoNome;
                        double novoPreco;

                        cout << "Digite o novo nome do produto: ";
                        cin.ignore();
                        getline(cin, novoNome);

                        cout << "Digite o novo preço do produto: ";
                        cin >> novoPreco;

                        editarProduto(produtos, indice - 1, novoNome, novoPreco);

                        cout << "Produto editado com sucesso!" << endl << endl;
                    } else if (opcao == 4) {
                        listarProdutos(produtos);
                    } else if (opcao == 5) {
                        mostrarPotencialVenda(produtos);
                    }
                } while (opcao != 0);
            } else {
                cout << "Senha incorreta. Acesso negado." << endl << endl;
            }
        }
    } while (modo != 0);

    return 0;
}

