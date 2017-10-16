import matplotlib.pyplot as plt

a=[1, 2, 4, 8, 16, 2, 1, 1, 1, 8]
b=[2, 2, 2, 2, 4, 1, 1, 1, 4, 4]
c=[0, 0, 0, 0, 0, 1, 1, 1, 0, 0]
d=[0, 0, 0, 0, 0, 0, 0, 1, 1, 8]
e=[1, 1, 1, 1, 1, 1, 1, 1, 2, 2]
f=[0, 0, 0, 0, 0, 0, 0, 2, 0, 0]
n=[50, 100, 200, 400, 800, 1000, 2000, 4000, 8000, 16000, 32000, 64000, 128000]
tempo_tot_filenames = []
tempos_filenames = []
chamadas_filenames = []
tempos_tot_plotnames = []
tempos_teo_plotnames = []
chamadas_nivel_plotnames = []
tempos_nivel_plotnames = []

for i in xrange(0,9):
	for j in xrange(0,3):
		tempos_tot_plotnames.append("tempos_tot_plot_" + str(a[i]) + str(b[i]) + str(c[i]) + str(d[i]) + str(e[i]) + str(f[i]) + str(j) + ".png")
		tempos_teo_plotnames.append("tempos_teo_plot_" + str(a[i]) + str(b[i]) + str(c[i]) + str(d[i]) + str(e[i]) + str(f[i]) + str(j) + ".png")
		for k in n:
			tempo_tot_filenames.append("tempo_tot_" + str(a[i]) + str(b[i]) + str(c[i]) + str(d[i]) + str(e[i]) + str(f[i]) + str(j) + str(k))
			tempos_filenames.append("tempos_" + str(a[i]) + str(b[i]) + str(c[i]) + str(d[i]) + str(e[i]) + str(f[i]) + str(j) + str(k))
			chamadas_filenames.append("chamadas_" + str(a[i]) + str(b[i]) + str(c[i]) + str(d[i]) + str(e[i]) + str(f[i]) + str(j) + str(k))
			chamadas_nivel_plotnames.append("chamadas_nivel_plot_" + str(a[i]) + str(b[i]) + str(c[i]) + str(d[i]) + str(e[i]) + str(f[i]) + str(j) + str(k) + ".png")
			tempos_nivel_plotnames.append("tempos_nivel_plot_" + str(a[i]) + str(b[i]) + str(c[i]) + str(d[i]) + str(e[i]) + str(f[i]) + str(j) + str(k) ".png")
		

for i in xrange(0, len(tempos_tot_plotnames)):
	tempos_tot_medias = []
	tempos_teo_medias = []
	for x in xrange(0, len(n)):
		tempos_totais = []
		tempos_teoricos = []
		with open(tempo_tot_filenames[i + x], 'r') as f:
			for line in f:
				valores = line.rstrip().split(" ")
				tempos_totais.append(float(valores[0]))
				tempos_teoricos.append(float(valores[1]))
		print(tempos_totais)
		print(tempos_teoricos)
		tempos_tot_medias.append(sum(tempos_totais)/len(tempos_totais))
		tempos_teo_medias.append(sum(tempos_teoricos)/len(tempos_teoricos))
	plt.plot(n, tempos_tot_medias)
	plt.ylabel("T(n)")
	plt.xlabel("n")
	plt.savefig(tempos_tot_plotnames[i])
	plt.clf()
	if -1 not in tempos_teo_medias:
		plt.plot(n, tempos_teo_medias)
		plt.ylabel("T(n) segundo o metodo mestre")
		plt.xlabel("n")
		plt.savefig(tempos_teo_plotnames[i])
		plt.clf()
	print tempos_tot_medias

for i in xrange(0, len(tempos_nivel_plotnames)):
	medias_arquivos = []
	with open(tempos_filenames[0], 'r') as f:
		media_arquivo = []
		for line in f:
			valores = line.rstrip().split(" ")
			media_arquivo.append(valores)
	for j in xrange(0, len(media_arquivo[0])):
		medias_arquivos.append(0);
	for arr in media_arquivo:
		for j in xrange(0, len(arr)):
			medias_arquivos[j] = medias_arquivos[j] + float(arr[j])
	for j in xrange(0, len(medias_arquivos)):
		medias_arquivos[j] = medias_arquivos[j] / (len(media_arquivo))
	print medias_arquivos
	plt.plot(range(1, len(medias_arquivos) + 1), medias_arquivos, 'ro')
	plt.ylabel("Tempo de execucao em cada nivel da arvore")
	plt.xlabel("nivel da arvore")
	plt.savefig(tempos_nivel_plotnames[i])
	plt.clf()

for i in xrange(0, len(chamadas_nivel_plotnames)):
	medias_arquivos = []
	with open(chamadas_filenames[0], 'r') as f:
		media_arquivo = []
		for line in f:
			valores = line.rstrip().split(" ")
			media_arquivo.append(valores)
	for j in xrange(0, len(media_arquivo[0])):
		medias_arquivos.append(0);
	for arr in media_arquivo:
		for j in xrange(0, len(arr)):
			medias_arquivos[j] = medias_arquivos[j] + int(arr[j])
	for j in xrange(0, len(medias_arquivos)):
		medias_arquivos[j] = medias_arquivos[j] / (len(media_arquivo))

	print medias_arquivos

	plt.plot(range(1, len(medias_arquivos) + 1), medias_arquivos, 'ro')
	plt.ylabel("chamadas recursivas em cada nivel arvore")
	plt.xlabel("nivel da arvore")
	plt.savefig(chamadas_nivel_plotnames[i])
	plt.clf()

