# Sistema de Controle de Estoque
Este projeto foi desenvolvido em linguagem C com o objetivo de implementar um sistema de controle de estoque funcional, com interface de linha de comando (CLI). 
##  Objetivo do Projeto
O sistema permite realizar as seguintes operações:
- Cadastrar produtos com código, nome, descrição, quantidade e preço unitário
- Consultar produtos por nome ou código
- Registrar entrada e saída de produtos no estoque
- Gerar relatórios salvos em arquivo `.txt`
- Persistir todos os dados em arquivos binários
##  Estrutura do Projeto

├── src/ # Código-fonte principal (main.c)

├── include/ # Arquivo de cabeçalho (estoque.h)

├── data/ # Arquivos binários e relatórios

├── docs/ # Documentação 

├── testes/ # Testes 

├── .gitignore

└── README.md

##  Como compilar e executar
### Compilação:
```bash
gcc src/main.c

-o estoque

Execução:

./estoque

 Forma de uso:

Ao executar o programa, o usuário encontrará um menu com as seguintes opções:

1 - Cadastrar novo produto

2 - Consultar produto (por nome ou código)

3 - Registrar entrada de produto

4 - Registrar saída de produto

5 - Gerar relatório em arquivo .txt

0 - Sair d sistema

Dados

Os produtos são armazenados em data/produtos.dat (binário)

Os relatórios são gerados em data/relatorio.txt (texto)

 Participantes

Nome:	Henrique Bassan	[22.223.083-1]

 Observações Finais

O projeto foi inteiramente desenvolvido com uso de GitHub Codespaces e versionado com Git, seguindo a estrutura exigida pelo enunciado.


