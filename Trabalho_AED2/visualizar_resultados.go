package main

import (
	"encoding/json"
	"fmt"
	"image/color"
	"os"
	"path/filepath"
	"sort"

	"github.com/pterm/pterm"
	"gonum.org/v1/plot"
	"gonum.org/v1/plot/plotter"
	"gonum.org/v1/plot/vg"
	"gonum.org/v1/plot/vg/draw"
)

// Algoritmo armazena dados de um algoritmo
type Algoritmo struct {
	Nome            string    `json:"nome"`
	Algoritmo       string    `json:"algoritmo"`
	Tamanho         int       `json:"tamanho"` // Essencial para o eixo X
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
	pterm.Info.Println("A ler ficheiros de dados gerados...")
	pterm.Println()

	workDir, err := os.Getwd()
	if err != nil {
		pterm.Error.Println("Erro ao obter diretório:", err)
		return
	}

	// ADICIONADO: A Questão 5 agora faz parte do pipeline de visualização
	questoes := []struct {
		nome      string
		arquivo   string
		descricao string
	}{
		{"questao01", "questao01_dados.json", "Q1: Busca Sequencial vs Binária (1M)"},
		{"questao02", "questao02_dados.json", "Q2: Busca em Vetor vs Lista (1M)"},
		{"questao03", "questao03_dados.json", "Q3: Ordenação (100k)"},
		{"questao05_ord", "questao05_ordena_dados.json", "GRÁFICO: Ordenações (10k a 100k)"},
		{"questao05_busca", "questao05_busca_dados.json", "GRÁFICO: Buscas (100k a 1 Milhão)"},
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

		// Exibir tabela no terminal
		exibirTabela(q.descricao, dados)

		if q.nome == "questao05_ord" || q.nome == "questao05_busca" {
			gerarGraficoComparativo(q.nome, q.descricao, dados.Algoritmos)
		}
	}

	if arquivosEncontrados == 0 {
		pterm.Error.Println("❌ Nenhum arquivo de dados foi encontrado!")
		pterm.Info.Println("Execute os programas em C primeiro.")
		return
	}

	pterm.Println()
	pterm.Success.Println("✅ Visualização e geração de gráficos concluídas com sucesso!")
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
		tableData := pterm.TableData{
			{"Métrica", "Valor"},
			{"Algoritmo", algo.Nome},
		}

		// Só exibe o tamanho se ele for maior que 0
		if algo.Tamanho > 0 {
			tableData = append(tableData, []string{"Tamanho (N)", fmt.Sprintf("%d", algo.Tamanho)})
		}
		
		tableData = append(tableData, []string{"Média (ms)", fmt.Sprintf("%.6f", algo.Media)})

		if algo.DesvioPadrao > 0 {
			tableData = append(tableData, []string{"Desvio Padrão (ms)", fmt.Sprintf("%.6f", algo.DesvioPadrao)})
		}

		tableData = append(tableData, []string{"Execuções", fmt.Sprintf("%d", algo.NumeroExecucoes)})

		if len(algo.TemposExecucao) > 0 && algo.NumeroExecucoes > 1 {
			tableData = append(tableData, []string{"", ""})
			tableData = append(tableData, []string{"Tempos Individuais", ""})

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
		}

		err := pterm.DefaultTable.WithHasHeader(true).WithData(tableData).Render()
		if err != nil {
			pterm.Error.Println("Erro ao renderizar tabela:", err)
		}
		pterm.Println()
	}

	if len(dados.Algoritmos) > 1 {
		exibirResumoComparativo(dados.Algoritmos)
	}
}

// exibirResumoComparativo exibe um resumo comparativo entre algoritmos
func exibirResumoComparativo(algoritmos []Algoritmo) {
	pterm.Println()
	pterm.DefaultSection.Println("📊 Resumo Comparativo")

	tableData := pterm.TableData{
		{"Algoritmo", "Tamanho", "Média (ms)", "Desvio Padrão", "Execuções"},
	}

	sort.Slice(algoritmos, func(i, j int) bool {
		return algoritmos[i].Media < algoritmos[j].Media
	})

	for i, algo := range algoritmos {
		posicao := fmt.Sprintf("%d. %s", i+1, algo.Nome)
		tamanhoStr := "-"
		if algo.Tamanho > 0 {
			tamanhoStr = fmt.Sprintf("%d", algo.Tamanho)
		}

		tableData = append(tableData, []string{
			posicao,
			tamanhoStr,
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

// gerarGraficoComparativo agrupa os dados por algoritmo e plota as linhas
func gerarGraficoComparativo(nomeArquivoBase string, titulo string, algoritmos []Algoritmo) {
	p := plot.New()
	p.Title.Text = titulo
	p.X.Label.Text = "Tamanho da Estrutura (N)"
	p.Y.Label.Text = "Tempo Médio (ms)"

	dadosPorAlgoritmo := make(map[string]plotter.XYs)

	for _, alg := range algoritmos {
		nomeGrupo := alg.Nome

		if alg.Tamanho == 0 {
			continue
		}

		dadosPorAlgoritmo[nomeGrupo] = append(dadosPorAlgoritmo[nomeGrupo], plotter.XY{
			X: float64(alg.Tamanho),
			Y: alg.Media,
		})
	}

	cores := []color.RGBA{
		{R: 0, G: 102, B: 204, A: 255},   // Azul forte
		{R: 204, G: 0, B: 0, A: 255},     // Vermelho
		{R: 0, G: 153, B: 51, A: 255},    // Verde
		{R: 255, G: 128, B: 0, A: 255},   // Laranja
		{R: 102, G: 0, B: 204, A: 255},   // Roxo
	}
	corIdx := 0

	for nomeGrupo, pts := range dadosPorAlgoritmo {
		sort.Slice(pts, func(i, j int) bool {
			return pts[i].X < pts[j].X
		})

		linha, err := plotter.NewLine(pts)
		if err != nil {
			continue
		}

		pontos, err := plotter.NewScatter(pts)
		if err != nil {
			continue
		}

		corAtual := cores[corIdx%len(cores)]
		linha.Color = corAtual
		linha.Width = vg.Points(2)
		pontos.Color = corAtual
		pontos.Shape = draw.CircleGlyph{}

		p.Add(linha, pontos)
		p.Legend.Add(nomeGrupo, linha, pontos)

		corIdx++
	}

	p.Legend.Top = true
	p.Legend.Left = true

	nomeSaida := fmt.Sprintf("%s_grafico.png", nomeArquivoBase)
	if err := p.Save(8*vg.Inch, 5*vg.Inch, nomeSaida); err != nil {
		pterm.Error.Printf("❌ Erro ao salvar gráfico %s: %v\n", nomeSaida, err)
	} else {
		pterm.Success.Printf("📈 Gráfico gerado e salvo como: %s\n", nomeSaida)
	}
}