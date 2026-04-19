package main

import (
	"encoding/json"
	"fmt"
	"os"
	"path/filepath"
	"sort"

	"github.com/pterm/pterm"
)

// Algoritmo armazena dados de um algoritmo
type Algoritmo struct {
	Nome            string    `json:"nome"`
	Algoritmo       string    `json:"algoritmo"`
	Media           float64   `json:"media"`
	DesvioPadrao    float64   `json:"desvio_padrao"`
	NumeroExecucoes int       `json:"numero_execucoes"`
	TemposExecucao  []float64 `json:"tempos_execucao"`
}

// DadosQuestao armazena os dados de uma questão
type DadosQuestao struct {
	Questao    string      `json:"questao"`
	Algoritmos []Algoritmo `json:"algoritmos"`
	Timestamp  string      `json:"timestamp"`
}

func main() {
	pterm.DefaultHeader.WithFullWidth(false).Println("📊 VISUALIZAÇÃO DE RESULTADOS - AED II")
	pterm.Info.Println("Lendo arquivos de dados gerados...")
	pterm.Println()

	workDir, err := os.Getwd()
	if err != nil {
		pterm.Error.Println("Erro ao obter diretório:", err)
		return
	}

	questoes := []struct {
		nome      string
		arquivo   string
		descricao string
	}{
		{"questao01", "questao01_dados.json", "Busca Sequencial vs Binária"},
		{"questao02", "questao02_dados.json", "Busca em Vetor vs Lista"},
		{"questao03", "questao03_dados.json", "Algoritmos de Ordenação"},
	}

	arquivosEncontrados := 0

	for _, q := range questoes {
		caminhoArquivo := filepath.Join(workDir, q.arquivo)

		// Verificar se arquivo existe
		if _, err := os.Stat(caminhoArquivo); os.IsNotExist(err) {
			pterm.Warning.Printf("⚠️  Arquivo não encontrado: %s\n", q.arquivo)
			continue
		}

		arquivosEncontrados++

		// Ler arquivo JSON
		dados, err := lerArquivoJSON(caminhoArquivo)
		if err != nil {
			pterm.Error.Printf("Erro ao ler %s: %v\n", q.arquivo, err)
			continue
		}

		// Exibir tabela
		exibirTabela(q.descricao, dados)
	}

	if arquivosEncontrados == 0 {
		pterm.Error.Println("❌ Nenhum arquivo de dados foi encontrado!")
		pterm.Info.Println("Execute os programas C (questao01.exe, questao02.exe, questao03.exe) primeiro.")
		return
	}

	pterm.Success.Println("✅ Visualização concluída com sucesso!")
}

// lerArquivoJSON lê e desserializa um arquivo JSON
func lerArquivoJSON(caminhoArquivo string) (*DadosQuestao, error) {
	conteudo, err := os.ReadFile(caminhoArquivo)
	if err != nil {
		return nil, err
	}

	var dados DadosQuestao
	err = json.Unmarshal(conteudo, &dados)
	if err != nil {
		return nil, err
	}

	return &dados, nil
}

// exibirTabela exibe uma tabela formatada com os dados
func exibirTabela(descricao string, dados *DadosQuestao) {
	pterm.Println()
	pterm.DefaultHeader.WithFullWidth(false).Printf("📈 %s\n", descricao)
	pterm.Println()

	for _, algo := range dados.Algoritmos {
		// Criar tabela para este algoritmo
		tableData := pterm.TableData{
			{"Métrica", "Valor"},
			{"Algoritmo", algo.Nome},
			{"Média (ms)", fmt.Sprintf("%.6f", algo.Media)},
		}

		if algo.DesvioPadrao > 0 {
			tableData = append(tableData, []string{"Desvio Padrão (ms)", fmt.Sprintf("%.6f", algo.DesvioPadrao)})
		}

		tableData = append(tableData, []string{"Execuções", fmt.Sprintf("%d", algo.NumeroExecucoes)})

		// Adicionar tempos individuais se houver
		if len(algo.TemposExecucao) > 0 {
			tableData = append(tableData, []string{"", ""})
			tableData = append(tableData, []string{"Tempos Individuais", ""})

			// Mostrar apenas até 15 tempos para não ficar muito grande
			limite := len(algo.TemposExecucao)
			if limite > 15 {
				limite = 15
			}

			for i := 0; i < limite; i++ {
				tableData = append(tableData, []string{
					fmt.Sprintf("  Exec %2d", i+1),
					fmt.Sprintf("%.6f", algo.TemposExecucao[i]),
				})
			}

			if len(algo.TemposExecucao) > 15 {
				tableData = append(tableData, []string{
					fmt.Sprintf("  ... (%d mais)", len(algo.TemposExecucao)-15),
					"",
				})
			}
		}

		// Renderizar tabela
		err := pterm.DefaultTable.WithHasHeader(true).WithData(tableData).Render()
		if err != nil {
			pterm.Error.Println("Erro ao renderizar tabela:", err)
		}
		pterm.Println()
	}

	// Exibir resumo comparativo se houver múltiplos algoritmos
	if len(dados.Algoritmos) > 1 {
		exibirResumoComparativo(dados.Algoritmos)
	}
}

// exibirResumoComparativo exibe um resumo comparativo entre algoritmos
func exibirResumoComparativo(algoritmos []Algoritmo) {
	pterm.Println()
	pterm.DefaultSection.Println("📊 Resumo Comparativo")

	// Criar tabela comparativa
	tableData := pterm.TableData{
		{"Algoritmo", "Média (ms)", "Desvio Padrão", "Execuções"},
	}

	// Ordenar por média (melhor para pior)
	sort.Slice(algoritmos, func(i, j int) bool {
		return algoritmos[i].Media < algoritmos[j].Media
	})

	for i, algo := range algoritmos {
		posicao := fmt.Sprintf("%d. %s", i+1, algo.Nome)
		tableData = append(tableData, []string{
			posicao,
			fmt.Sprintf("%.6f", algo.Media),
			fmt.Sprintf("%.6f", algo.DesvioPadrao),
			fmt.Sprintf("%d", algo.NumeroExecucoes),
		})
	}

	err := pterm.DefaultTable.WithHasHeader(true).WithData(tableData).Render()
	if err != nil {
		pterm.Error.Println("Erro ao renderizar tabela:", err)
	}
	pterm.Println()
}
