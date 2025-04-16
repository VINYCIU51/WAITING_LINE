#include <iostream>
#include <queue>
#include <vector>
#include <string>
#include <map>
#include <fstream>
#include <iomanip>

using namespace std;

struct Paciente
{
    string nome;
    int prioridade;
    int tempoAtendimento;

    Paciente(string n, int p, int t) : nome(n), prioridade(p), tempoAtendimento(t) {}

    bool operator<(const Paciente &outro) const
    {
        return prioridade > outro.prioridade;
    }
};

map<int, string> cores = {
    {1, "Vermelho"},
    {2, "Laranja"},
    {3, "Amarelo"},
    {4, "Verde"},
    {5, "Azul"}};

priority_queue<Paciente> fila;
vector<Paciente> atendidos;

bool prioridadeValida(int prioridade)
{
    return prioridade >= 1 && prioridade <= 5;
}

void adicionarPaciente()
{
    string nome;
    int prioridade;
    int tempoAtendimento;

    cout << "Nome do paciente: ";
    getline(cin >> ws, nome);

    do
    {
        cout << "Prioridade (1 a 5): ";
        cin >> prioridade;
        if (!prioridadeValida(prioridade))
        {
            cout << "Prioridade inválida! Tente novamente.\n";
        }
    } while (!prioridadeValida(prioridade));

    cout << "Tempo de atendimento (em minutos): ";
    cin >> tempoAtendimento;

    fila.push(Paciente(nome, prioridade, tempoAtendimento));
    cout << "Paciente adicionado com prioridade " << cores[prioridade] << "!\n";
}

void atenderPaciente()
{
    if (fila.empty())
    {
        cout << "Nenhum paciente na fila.\n";
        return;
    }

    Paciente p = fila.top();
    fila.pop();
    atendidos.push_back(p);

    cout << "Atendendo paciente: " << p.nome << " | Prioridade: " << cores[p.prioridade] << endl;
}

void listarFila()
{
    if (fila.empty())
    {
        cout << "Fila vazia.\n";
        return;
    }

    priority_queue<Paciente> copia = fila;
    cout << "Fila de pacientes:\n";
    while (!copia.empty())
    {
        Paciente p = copia.top();
        copia.pop();
        cout << "Nome: " << p.nome << " | Prioridade: " << cores[p.prioridade] << " | Tempo: " << p.tempoAtendimento << " min\n";
    }
}

void calcularTempoMedio()
{
    if (atendidos.empty())
    {
        cout << "Nenhum paciente atendido.\n";
        return;
    }

    int soma = 0;
    for (const auto &p : atendidos)
    {
        soma += p.tempoAtendimento;
    }

    double media = static_cast<double>(soma) / atendidos.size();
    cout << fixed << setprecision(2);
    cout << "Tempo médio de atendimento: " << media << " minutos.\n";
}

void exportarRelatorio()
{
    ofstream arquivo("relatorio.txt");
    if (!arquivo)
    {
        cerr << "Erro ao criar o arquivo.\n";
        return;
    }

    arquivo << "Relatório de Pacientes Atendidos:\n";
    for (const auto &p : atendidos)
    {
        arquivo << "Nome: " << p.nome << " | Prioridade: " << cores[p.prioridade] << " | Tempo: " << p.tempoAtendimento << " min\n";
    }

    arquivo.close();
    cout << "Relatório exportado como 'relatorio.txt'.\n";
}

void buscarPorNome()
{
    string nome;
    cout << "Digite o nome a buscar: ";
    getline(cin >> ws, nome);

    priority_queue<Paciente> copia = fila;
    bool encontrado = false;

    while (!copia.empty())
    {
        Paciente p = copia.top();
        copia.pop();
        if (p.nome == nome)
        {
            cout << "Paciente encontrado: " << p.nome << " | Prioridade: " << cores[p.prioridade] << " | Tempo: " << p.tempoAtendimento << " min\n";
            encontrado = true;
            break;
        }
    }

    if (!encontrado)
    {
        cout << "Paciente não encontrado na fila.\n";
    }
}

void menu()
{
    int opcao;

    do
    {
        cout << "\n======= SIMULADOR DE FILA HOSPITALAR =======\n";
        cout << "1. Adicionar paciente\n";
        cout << "2. Atender próximo paciente\n";
        cout << "3. Listar fila de pacientes\n";
        cout << "4. Calcular tempo médio de atendimento\n";
        cout << "5. Exportar relatório\n";
        cout << "6. Buscar paciente por nome\n";
        cout << "0. Sair\n";
        cout << "Escolha: ";
        cin >> opcao;

        switch (opcao)
        {
        case 1:
            adicionarPaciente();
            break;
        case 2:
            atenderPaciente();
            break;
        case 3:
            listarFila();
            break;
        case 4:
            calcularTempoMedio();
            break;
        case 5:
            exportarRelatorio();
            break;
        case 6:
            buscarPorNome();
            break;
        case 0:
            cout << "Encerrando...\n";
            break;
        default:
            cout << "Opção inválida!\n";
        }
    } while (opcao != 0);
}

int main()
{
    menu();
    return 0;
}
