%% init.m
% Programme d'initialisation pour le Contrôle en tension hacheur PV 
% ----------------------------------------------------------------
%		Créé par François GRUSON & Héloïse Lacroix le :	18-01-2023
%       Copyright 2019 L2EP - Arts et Métiers Science et Technologie
%       L2EP - Arts et Métiers Science et Technologie Lille
% ----------------------------------------------------------------
%       Co-réalisateurs: Dr. François GRUSON (ENSAM Lille) / Francois.GRUSON@ensam.eu
%                        Héloïse Lacroix (ENSAM Lille) / heloise.lacroix@polytech-lille.net
% ----------------------------------------------------------------


clear all;
clc; % remise a zéro du workspace

%% Paramètres de simulation
t_simul = 0.1;              % Temps de simulation
pas_calcul = 1e-6;        % Pas de calcul fixe

%%parametres extérieur PV, température et l'irradiance
E=1500; %irradiance W/m²
Tc=15+273; % T°C

%%parametres DC/DC
Vdc=60; %(V) du bus dc
Fmli=10000; % consigne en frequence de modulation
T=1/Fmli;


%parametres filtre DC/DC
In_PV=2.5; %courant nominal du PV
deltaI=In_PV* 5/100 % deltaI = 5% Inominal
Lmin=Vdc/(4*deltaI*Fmli); %inductance minimale

L=Lmin;
Rl=L; %resistance parasite de L


%% test régulation en courant
DeltaI=0.1;%largeur de la fourechette en courant
Iref=2;%courant de référence

%test régulation en tension
VpvREF=19;
 
%Déclaration des constantes 
Isc = 3.8;
Kisc = 0.024;

Tstc = 25+273;
Gstc = 1000;

q = 1.6*10^(-19);
a = 1.2;
K = 1.38*10^(-23);

Vco = 21.1;
Kvco = -0.08;

Ns = 36;
Np = 4;

Rs = 0.008;
Rsh = 1000;


% % Creation figure :
% figure1 = figure('NumberTitle','off','Name','I_{pv}=f(V_{pv} ; Ensoleillement)','Color',[1 1 1]);
% % creation nom et couleur arrière plan (1 1 1 : blanc)
% %%
% % Create axes
% axes1 = axes('Parent',figure1,'FontSize',14,'FontName','Times New Roman');
% 
% box(axes1,'on');
% hold(axes1,'on');
% xlim(axes1,[0.01 30]); %bornage des axes
% ylim(axes1,[0 5]);
% %%
% % Create plot
% sim 'PV_hacheur_PJT_MODIFIE.slx'
% plot (Vpv,Ipv,'LineWidth',2,'LineStyle','--','color','b','displayname','E=1200'); %r pour red; g pour green, b pour blue
% hold on;
% E=1000;
% sim 'PV_hacheur_PJT_MODIFIE.slx'
% plot (Vpv,Ipv,'LineWidth',2,'LineStyle','--','color','g','displayname','E=1000'); %r pour red; g pour green, b pour blue
% hold on;
% grid on; %grille activée
% 
% 
% % Create xlabel
% xlabel('V_{pv} (V)');
% 
% % Create ylabel
% ylabel('I_{pv} (A)');
