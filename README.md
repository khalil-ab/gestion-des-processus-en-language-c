Dans un système à temps partagé, plusieurs processus peuvent être présents en mémoire centrale en attente d’exécution. Si plusieurs processus sont prêts ou bloqués, le système d’exploitation doit gérer l’allocation d’une ressource aux différents processus à exécuter. C’est l’ordonnanceur (Scheduler en anglais) qui s’acquitte de cette tâche en utilisant un algorithme d'ordonnancement.
Les algorithmes d’ordonnancement aident donc l’ordonnanceur à sélectionner parmi les processus actifs celui qui va obtenir l’utilisation d’une ressource, que ce soit le processeur, ou bien un périphérique d’entrée sortie. 
C’est pour cela j’ai réalisé cette application de gestion des processus apellé ORDO-3P1B. 
ORDO-3P1B est donc une application informatique écrite en Language C, simple d'utilisation et qui permet de gérer les processus d'un programme quelconque.

Ce programme peut être utilisé par les programmeurs, les étudiants ou les amateurs d'informatique, pour savoir comment seront gérés les processus d'un programme à l'aide d'une grille bien présentée avec des commentaires explicatifs.

Très facile à maîtriser, ORDO-3P1B permet de suivre instantanément l'évolution d'un programme en répondant très facilement aux besoins des utilisateurs.

C’est en utilisant le logiciel de programmation CodeBlocks que j'ai pu programmer ORDO-3P1B. L’établissement d’une telle application a pris beaucoup  de temps à cause de la multitude des risques d’erreurs qui peuvent se produire ainsi que la grande difficulté de trouver la démarche que le programme va suivre pour réaliser le travail demandé car il existe plusieurs qu'il faut prendre en considération. Heureusement j'ai pu régler presque la totalité des risques et algorithmes d'ordonnancement.
Les consignes du projet :

Ce projet parle de la création d'une application de gestion des processus en utilisant trois types d'algorithmes d'ordonnancement pour les processus prêts et un seul type d'algorithme d'ordonnancement pour les processus bloqués.  
Le système dont nous somme entrain d'étudier dispose d'un seul processeur et il s'agit d'implémenter trois types d'algorithmes d'ordonnancement pour les processus prêts et qui sont :

1.	FIFO (First In First Out) : appelé aussi FCFS (First Come First Served), c'est l'un des algorithmes les plus simples qu'il soit. L'idée est d'ajouter chaque processus dans une file et d'exécuter chaque processus par ordre d'arrivée.

2.	Le tourniquet (Round-Robin) avec un TC=1 : les processus accèdent au processeur, chacun à leur tour, pendant un temps déterminé à l'avance (le quantum), c'est à dire que lorsque le processus a accès au processeur, il ne peut l'utiliser que pendant un certain Quantum de temps qt, et à l'expiration de ce quantum de temps, ou s'il a fini son temps d'exécution il laisse automatiquement sa place pour le processus suivant. Un temps de commutation pendant 1ms est nécessaire avant chaque début et après chaque fin d'utilisation du processeur. De même on suppose que les processus finissant une entrée-sortie au même moment qu'un autre finissant son quantum est plus prioritaire pour accéder au CPU.

3.	Priorité avec réquisition : Dans une file d'attente, le prochain processus sélectionné est celui ayant la plus grande priorité.  Quand un processus se voit retirer le processeur à un instant quelconque, il est remis dans la file en tête.
Le seul type d'ordonnancement pour les processus bloqués s'appelle : 
•	SJF (Short Job First) : L'algorithme SJF (plus court d'abord) ressemble au FIFO mais au lieu d'exécuter dans l'ordre d'arrivée, on choisi d'exécuter celui qui a le plus court temps d'execution.
Il faut noter aussi que chaque processus est périodique, et est caractérisé par des informations chargées par le programme à partir d'un fichier de type TXT. Chaque ligne de ce dernier est composée des données suivantes séparées par un point virgule : 
•	Le code qui identifie le processus de manière unique
•	La date d'arrivée du processus
•	La priorité du processus
•	Le temps d'exécution du processus
•	Le temps d'entrée sortie du processus

Lorsque le programme est en marche, l'utilisateur charge le fichier TXT contenant le BCP de chaque processus ensuite il choisit le type d'algorithme d'ordonnancement du premier cas (sans état bloqué) ou deuxième cas (avec état bloqué), il précise le temps d'arrêt (N) puis il reçoit la grille qui résume comment les processus partageront le processeur avec ou sans périphérique d'entrée-sortie pendant les N premières unités selon le cas utilisé  et selon le type d'algorithme choisis.  

<p align="center">
  <img src="/0.png">
</p>
<p align="center">
  <img src="/1.png">
</p>
<p align="center">
  <img src="/2.png">
</p>
<p align="center">
  <img src="/3.png">
</p>
<p align="center">
  <img src="/4.png">
</p>
<p align="center">
  <img src="/5.png">
</p>
<p align="center">
  <img src="/6.png">
</p>

Voici le lien de la simulation en video : https://youtu.be/LL51QYcd0Vs

Voici mon email si quelqu'un voudrait me contacter : abouabdelmajidkhalil@gmail.com
