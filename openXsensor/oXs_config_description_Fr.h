/*
*************************************************************************************
*                                  Information importante:
*  Ne pas modifier ce fichier a mois de vouloir y a jouter vos propre commentaire.
*  Ce fichier a pour but de fournir des explications pour le fichier oXs_config.h.
*  La configuration doit être faite dans le fichier oXs_config.h
*************************************************************************************

Voir le github OpenXsensor https://github.com/openXsensor/
Ecrit par par Rainer Schlosshan traduction Thierry ZINK

************************************************************************************************************************
************************************* description général de toute les options *****************************************
************************************************************************************************************************
*  le fichier oXs_config.h permet aux utilisateurs de configurer différentes options. Voici la liste des différentes options.
*  
*  1 - Choix du protocole de télémétrie
*    1.1 - Sélection de la sortie vers le récepteur
*    1.2 - SPORT_SENSOR_ID (utilisé unique pour le protocol FrSky Sport)
*  2 - Données a transmettre a l'émetteur
*  3 - réglage de la sortie PPM(optionnel)
*  4 - Réglage Vario (le vario est optionnel)
*   4.1 - Connections de 1 ou 2 capteurs barométriques 
*   4.2 - Type de vitesse vertical envoyer
*   4.3 - Sensibilité predefinie par programation
*   4.4 - Sensibilité ajuster depuis l'emmeteur
*   4.5 - Parametre hysteresis & compensation de l'altitude a partir du capteur de temperature 
*   4.6 - Calcule de la vitesse vertical baser sur le signal PPM (option)
*   4.7 - Vitesse vertical analogique (optionnel)
*   4.8 - Calcul des performances du planeur, calcul moyen des tôt de monter/descente, calcul moyen de l’altitude gagner/perdu (optionel)
*  5 – Réglage de la sonde de Pitot (optionnel)
*  6 – Réglage capteur de tension et de courant (optionnel)
*   6.1 - Tension de référence pour mesure des tensions et des courants
*   6.2 - Paramètres des tensions
*   6.3 - Maximum de cellule LiPo mesurer (et envoyer a l’émetteur)
*   6.4 - Conversion de tension en température (° Celcius)     
*   6.5 - Paramètre des capteurs de mesure de courant.
*   6.6 - Paramètres de Ads1115
*  7 - Réglage capteur RPM (tour par minute) (optionnel))
*  8 - Réglage de la mémoire non volatile (optionnel)
*  9 - GPS (optionnel)
*  10 - IMU 6050 (capteur accéléromètre/gyroscope) (optionnel)  et HMC5883 (magnetometre)
*  11 - Capteur de débit 
*  20 - Séquenceur  (ON/OFF) pour certaine sortie digitale (Exemple : contrôle de lumière)
*  xx – Réserver au développeur
*
* Note: Les paramètres activé commence par  "#define",  suivi du nom du paramètre et dans la majorité des cas d’une valeur pour ce paramètre
*        Pour activé ou désactivé les paramètres il faut supprimer ou ajouté les "//" qui précède "#define" Example “// #define ParameterToto Bonjour“ le ParametreToto ne sera pas pris en compte car pour Arduino c’est considérer comme un commentaire. 
************************************************************************************************************************



**** 1 - Choix du protocole de télémétrie **********************************************************************
* Actuellement oXs supports 4 protocoles de télémétrie: Multiplex , Frsky, Jeti and Hott (=Graupner)
* Un et uniquement un protocole peut-être sélection; Exemple si vous active le protocole Multiplex, les protocoles Frsky, Jeti et Hott sont désactivé (et vice et versa) 
* FrSky utilise 2 protocoles différents :
*       - SPORT utilisé par les récepteurs de la série X (comme le X8R ou X6R)
*       - HUB utilisé par les récepteurs de la série D (comme le D4R-II)
*      oXs peut supporter les deux protocoles FrSky en même temps (en utilisant l’option FRSKY_SPORT_HUB). oXs peut automatiquement détecter le type de récepteur auquel il est connecté
*      Si vous utilisez cette option vous n’aurez pas besoin de reprogrammer votre oXs si vous passez d’un récepteur série X à série D.
*      l’auto détection ne semble pas marcher a 100% et demande plus de mémoire…
*      Dans le cas de l’auto détection ne fonctionne pas ou si vous avez besoin de plus de mémoire (car vous utilisé beaucoup de capteur connecté à votre oXs), vous pouvez forcer sur le protocole FRSKY spécifique que vous utilisez
*  Pour sélectionné le protocole utilise par oXs remplir la ligne #define PROTOCOL avec le nom du protocole sélectionné avec l’une des valeurs suivante: FRSKY_SPORT , FRSKY_HUB , FRSKY_SPORT_HUB , MULTIPLEX , HOTT; JETI
************************************************************************************************************************
#define PROTOCOL FRSKY_SPORT    // select between FRSKY_SPORT , FRSKY_HUB , FRSKY_SPORT_HUB , MULTIPLEX , HOTT, JETI


*  1.1 - Sélection de la sortie vers le récepteur ***********************************************************************************************
*   oXs doit être connecté a récepteur afin de transmettre les informations.
*   Pour cela, une sortie DIGITAL de l’arduino doit être connectée au récepteur.
*   Vous devez spécifier la PIN arduino utilisé pour cette fonction.
*   Valeur par défaut: 4 ; Les valeurs autorisées sont 2 ou 4 mais faite attention de ne pas utiliser la même PIN pour 2 fonction. 
************************************************************************************************************************
#define PIN_SERIALTX  4

*  1.2 ****** SPORT_SENSOR_ID (utilisé unique pour le protocol FrSky Sport) **********************    
*  
*      Pour le protocole SPORT, il peut y avoir plusieurs capteur connecté sur le même bus  mais chaque capteur doit avoir un identifiant « SPORT_SENSOR_ID » diffèrent.
*           Pour le protocole SPORT, oXs peu utilisé jusqu’à 6 identifiant. Les 6 SPORT_SENSOR_ID utilisé par oXs sont :    
*               DATA_ID_VARIO  	0x00  	// = sensor 0 utilisé pour altitude et la vitesse vertical
*               DATA_ID_FLVSS  	0xA1 	//		    1 utilisé pour la mesure de élément de baterie
*               DATA_ID_FAS		0x22  	//         	2 utilisé pour vfas, courant et carburant
*               DATA_ID_GPS		0x83  	//          3 utilisé pour les données GPS
*               DATA_ID_RPM		0xE4  	//          4 utilisé pour les rpm, T1, T2, et la sonde de pitot
*               DATA_ID_ACC		0x67  	//          7 utilisé poue Acceleration sur X, Y, Z
*               Si besoin (par exemple pour connecter 2 oXs envoyant deux donné identique), vous pouvez changer les valeur de SPORT_SENSOR_ID mais vous devez uniquement selectioner des adresse parmie les valeur suivante:
*                  0x00,0xA1,0x22,0x83,0xE4,0x45,0xC6,0x67,0x48,0xE9,0x6A,0xCB,0xAC,0x0D,0x8E,0x2F,0xD0,0x71,0xF2,0x53,0x34,0x95,0x16,0xB7,0x98,0x39,0xBA,0x1B
*               les valeurs du paramétre SPORT_SENSOR_ID sont défini dans le fichier oXs_config_advanced.h (section 1.1)
************************************************************************************************************************



**** 2 - Data to transmit **********************************************************************************************
*   selon les paramètres selection dans le fichié config.h (et les capteur connecté à oXs), oXs peux calculer plusieurs messures 
*   Pour le protocole Multiplex, vous devez spécifier quelle mesures doit être renvoyer a l'emmeteur (et sur quelle ligne de l'ecran de l'émmeteur il doit etre afficher) (voir ci dessous) 
*   Pour les protocoles SPORT, HUB, JETI et HOTT, les mesure sont automatique transmise dans le champs adapté et certain protocol autorise envoyer certain mesure en reutilisant certain champs.
*   Une de mesure effectuer est la "Vitesse vertical principale".
**** 2.1 Protocole FrSKY (SPORT et HUB ) ************************************************************************************ 
*      les meusure transmise automatiquement sont : 
*         - Altitude relative(cm), Vitesse vertical principale(cm/sec) (si au minimum un capteur barométrique est connecté)
*         - Tensions des cellules (si NUMBER_OF_CELLS > 0) 
*         - Courant (quand un capteur de courant est connecté)
*         - GPS (long, lat, vitesse, altitude , course) (quand un GPS est connecté)
*         - RPM (hz) (quand un capteur de vitesse de rotation est connecté)
*      En suplement de ces mesure, vous pouvez sepcifié les parametères des messures suivante Vfas, Fuel, A3, A4, T1, T2, AccX, AccY, AccZ (voir les option disponible ci-dessous)
*      Commenter toutes les lignes qui ne doive pas être transmise.
*    ex :  
*      #define VFAS_SOURCE VOLT_4                 // selectionné une valeur parmi: VOLT_1, VOLT_2, VOLT_3 , VOLT_4, VOLT_5 , VOLT_6, ADS_VOLT_1, ADS_VOLT_2, ADS_VOLT_3, ADS_VOLT_4
*      #define FUEL_SOURCE VOLT_4                 // selectionné une valeur parmi: VOLT_1, VOLT_2, VOLT_3 , VOLT_4, VOLT_5 , VOLT_6, ADS_VOLT_1, ADS_VOLT_2, ADS_VOLT_3, ADS_VOLT_4
*      #define A3_SOURCE VOLT_4                   // selectionné une valeur parmi: VOLT_1, VOLT_2, VOLT_3 , VOLT_4, VOLT_5 , VOLT_6, ADS_VOLT_1, ADS_VOLT_2, ADS_VOLT_3, ADS_VOLT_4
*      #define A4_SOURCE VOLT_4                   // selectionné une valeur parmi: VOLT_1, VOLT_2, VOLT_3 , VOLT_4, VOLT_5 , VOLT_6, ADS_VOLT_1, ADS_VOLT_2, ADS_VOLT_3, ADS_VOLT_4
*      #define ACCX_SOURCE TEST_1                 // selectionné une valeur parmi: TEST_1, TEST_2, TEST_3, GLIDER_RATIO , SECONDS_SINCE_T0 ,AVERAGE_VSPEED_SINCE_TO , VOLT_1, VOLT_2, VOLT_3, VOLT_4, VOLT_5, VOLT_6, PITCH, ROLL, YAW, ADS_VOLT_1, ADS_VOLT_2, ADS_VOLT_3, ADS_VOLT_4 
*      #define ACCY_SOURCE TEST_2                 // selectionné une valeur parmi: TEST_1, TEST_2, TEST_3, GLIDER_RATIO , SECONDS_SINCE_T0 ,AVERAGE_VSPEED_SINCE_TO , VOLT_1, VOLT_2, VOLT_3, VOLT_4, VOLT_5, VOLT_6, PITCH, ROLL, YAW, ADS_VOLT_1, ADS_VOLT_2, ADS_VOLT_3, ADS_VOLT_4 
*      #define ACCZ_SOURCE TEST_3                 // selectionné une valeur parmi: TEST_1, TEST_2, TEST_3, GLIDER_RATIO , SECONDS_SINCE_T0 ,AVERAGE_VSPEED_SINCE_TO , VOLT_1, VOLT_2, VOLT_3, VOLT_4, VOLT_5, VOLT_6, PITCH, ROLL, YAW, ADS_VOLT_1, ADS_VOLT_2, ADS_VOLT_3, ADS_VOLT_4 
*      #define T1_SOURCE GLIDER_RATIO             // selectionné une valeur parmi: TEST_1, TEST_2, TEST_3, GLIDER_RATIO , SECONDS_SINCE_T0 ,AVERAGE_VSPEED_SINCE_TO , SENSITIVITY , PPM, VOLT_1, VOLT_2, VOLT_3, VOLT_4, VOLT_5, VOLT_6, ADS_VOLT_1, ADS_VOLT_2, ADS_VOLT_3, ADS_VOLT_4 
*      #define T2_SOURCE SENSITIVITY              // selectionné une valeur parmi: TEST_1, TEST_2, TEST_3, GLIDER_RATIO , SECONDS_SINCE_T0 ,AVERAGE_VSPEED_SINCE_TO , SENSITIVITY , PPM, VOLT_1, VOLT_2, VOLT_3, VOLT_4, VOLT_5, VOLT_6, ADS_VOLT_1, ADS_VOLT_2, ADS_VOLT_3, ADS_VOLT_4
**** 2.2 Hott protocol ************************************************************************************ 
*      les meusure transmise automatiquement sont : 
*         - Altitude relative(cm), Vitesse vertical principale(cm/sec) (si au minimum un capteur barométrique est connecté)
*         - Tensions des cellules (si NUMBER_OF_CELLS > 0)
*         - jusqu'à trois mesure de tension de battery (le setupe specifie quelle tension doive être mesureret transmise - Exemple VOLT_1,VOLT_2, ...)  
*         - Courant (quand un capteur de courant est connecté)
*         - GPS (long, lat, vitesse, altitude , course) (quand un GPS est connecté)
*         - RPM (hz) (quand un capteur de vitesse de rotation est connecté)
*      Lorsque vous mesurez des tensions de bateries, une alarme peux etre regler pour indiqué les tensions inférieur a un niveau reglé.   
*      Pour activé cette alarme, dé commenter la ligne ci-dessous (en milliVolt) pour regler le seuille d'alarme
*         //#define CELL_UNDERVOLTAGE_WARNING 3300            // Attention c'est en mV;
*         
*      Vous pouvez aussi selectioné comment les valeurs temperature1 et temperature2 seront remplie 
*      note : ces deux champs peuvent selement retourner des valeurs allant de -20 à 235; pour le mode PPM une valeurs de -100 sera affiché 0 et +100 sera affiché 200      
*      Mettre les lignes ci-dessous en commentaire quand aucune mesures doivent être transmise par télémetry      
*     ex:  
*       #define BATTERY_1_SOURCE          VOLT_4                // selectionné une valeur parmi: VOLT_1, VOLT_2, VOLT_3 , VOLT_4, VOLT_5 , VOLT_6
*       #define BATTERY_2_SOURCE          VOLT_2                // selectionné une valeur parmi: VOLT_1, VOLT_2, VOLT_3 , VOLT_4, VOLT_5 , VOLT_6
*       #define MAIN_BATTERY_SOURCE       VOLT_5                // selectionné une valeur parmi: VOLT_1, VOLT_2, VOLT_3 , VOLT_4, VOLT_5 , VOLT_6
*       #define TEMPERATURE_1_SOURCE      TEST_1          		// selectionné une valeur parmi: TEST_1, TEST_2, TEST_3 , GLIDER_RATIO , SENSITIVITY , PPM
*       #define TEMPERATURE_2_SOURCE      SENSITIVITY          	// selectionné une valeur parmi: TEST_1, TEST_2, TEST_3 , GLIDER_RATIO , SENSITIVITY , PPM
**** 2.3 Multiplex  ************************************************************************************ 
*      Pour le protocole Multiplex, vous avez a définire quelle mesures de OXS sont transmise sur quelle ligne de l'emeteur.
*      Vous devez aussi spécifié les echelles qui doivent être appliqué par OXS et le range de valeur afin de definir le on/off des alarmes.
*      Vous DEVEZ specifie une ligne pour chaque mesure a envoyer a l'emmeteur. Chaque ligne doit contenir :
*        -  1 : le numero de ligne de l'ecran lde l'emmeteur ou doit etre afficher la mesure. Les valeur autorisées vont de 2 à 15, attention de ne pas utilisé deux foix la même valeur.
*        -  2 : une virgule
*        -  3 : les nom du parameter OXS qui doit être transmit sur cette ligne (exemple "VOLT_1")  (voir note (2))
*        -  4 : une virgule
*        -  5 : un coeficient multiplicateur a être appliqué sur la valeur transmise (mettre "1" pour conserver la mesure original, 10 pour multiplier la messure par 10 , ...) (voir note (3))
*        -  6 : une virgule
*        -  7 : un coeficient diviseur à être appliqué sur la valeur transmise (mettre "1" pour conserver la mesure original, 10 pour multiplier la messure par 10 , ...)  (voir note (3))
*        -  8 : une virgule
*        -  9 : offset appliquer sur la valeur apres avoir appliquer le coeficient multiplicateur et diviseur ((mettre "0" pour conserver la mesure d'origine, "100" pour ajouter 100, ...)
*        - 10 : une virgule
*        - 11 : une alarme pour la valeur minimum (voir note (4))
*        - 12 : une virgule
*        - 13 : une valeur pour la valeur haute (voir note (4))
*        - 14 : une virgule et une "\" si il y a une mesure apres celle ci (,\ a ne pas mettre pour la dernière mesure);
*                  /!\ ATTENTION que "\" doit être le dernier character de la ligne (aucun espace et tolleré après)
*                  /!\ ATTENTION que aucune ligne de commentaire ("*...") soit glisser entre les differentes lignes
* Note (2) : Une mesure OXS (exemple VOLT_1) ne peux pas etre déclarer dans plusieur limits.
* Note (3) : Les coeficient multiplicateur, diviseur et l'offset doit etre une valeur entière (pas de chiffre à virgule); ils peuvent être négatif (exemple "-100").
*            Les coeificien multiplicateur et diviseur peuvent etre utile dans las cas suivant:
*              - pour convertire d'un unité de mesure a une autre (meter <> pied)
*              - pour convertir en pourcentage (example multiplier par 100 et diviser par 4000 afin d'optenir un % de consomation pour un accu de 4000 mAmph)
*              - pour ajusté le nombre de digit afficher sur l'emmeteur.
*              - pour avoir par exemple une valeur de quantité de fuel commencent a 100 (en pourcent) et diminuent a 0 quand la comsomation augmente (dans ce cas vous devez utiliser un coeficient mutliplicateur négatif et un offset de 100%).
*            Multipicateur/diviseur/offset doivent être defini mais ne sont pas toujours utilisé par OXS. C'est le cas quand:
*              - CELLS_1_2, CELLS_3_4, CELLS_5_6 sont transmit (car ces champ requiere un formatage spéciaux requi par l'émmeteur)
* Note (4) : les limite d'alarme doivent etre des nombres entiés (pas de chiffre à virgule); ils peuvent être négatif (exemple "-100"). 
*                Afin de definir les alarmes demander dans le protocole Multiplex, OXS vas proceder de la facon suivante:
*                 - adapté le nombre de decimal de la mesure faite par OXS (la plupart des mesures de OXS ont plus de décimal que prévur par le protocol Multiplex)
*                 - appliqué les coeificents multiplicateur, diviseur et l'offset
*                 - comparé les résultats avec les niveaux haut et bas des alarmes
*               LEs limite doive etre fixé en tennant compte tous le digit visible a l'ecrant.
*                  Exemple: Les temsion sont afficher mVolt. Si vous voulez un alarme quand la tension est inferieur à 11.2 Volt, regler la valeur d'alarme minimum a 112.
*              afin d'inibé les alarme mettre la valeur minimum à -16384 et/ou la valeur maximal a 16383 (valeur minimal et maximal pour le protocole de type Multiplex sur 15 bits)
*   
* ci-dessous un exemple de reglage pour transmetre sur le protocole Multiplex
*     - sur la ligne 3, l'altitude relative mesurer (sans alarme)
*     - sur la ligne 6, la vitesse vertical measuer (avec une alarme si la valeur excede 50m/s)
*            #define SETUP_MULTIPLEX_DATA_TO_SEND    \
*                       3 , REL_ALTIMETER , 1 , 1 , 0 , -16384 , 16383,\
*                       6 , VERTICAL_SPEED , 1 , 1 , -500 , 500
*  /!\ IMPORTANT : toujours conservé la ligne "#define SETUP_DATA_TO_SEND    \"  ; ne pas inserer de ligne avant ou apres les lignes utiliser pour le setup.
*   
* Ici vous trouverez la liste des mesure que peux envoyer OXS.
*    Code a utilisez        Unité       Signification 
*    ALTIMETER           	m      		Absolute altitude (from first baro sensor)
*    REL_ALTIMETER       	m      		Relative altitude (from first baro sensor)  
*    ALTIMETER_MAX       	m      		Max relative altitude
*    VERTICAL_SPEED     	cm/s    	Main vertical speed (as set up in VSPEED_SOURCE)
*    SENSITIVITY        	none    	Vario sensitivity 
*    VOLT_1            		0.1V(5)     Value read on first PIN_VOLTAGE     
*    VOLT_2            		0.1V(5)     Value read on 2d PIN_VOLTAGE        
*    VOLT_3            		0.1V(5)     Value read on 3d PIN_VOLTAGE        
*    VOLT_4            		0.1V(5)     Value read on 4th PIN_VOLTAGE       
*    VOLT_5            		0.1V(5)     Value read on 5th PIN_VOLTAGE       
*    VOLT_6            		0.1V(5)     Value read on 6th PIN_VOLTAGE       
*    CURRENTMA         		0.1A        MilliAmp measured by current sensor  
*    MILLIAH           		mAh        	Consumed milli Amp heure             
*    RPM              		Hz         	Rotation per min                     
*    AIR_SPEED        		0.1 km/h   	Air speed   
*    CELL_1             	0.1V(5)    	Value based on first PIN_VOLTAGE         
*    CELL_2             	0.1V(5)    	Value based on first and 2d PIN_VOLTAGE  
*    CELL_3             	0.1V(5)    	Value based on 2d and 3d PIN_VOLTAGE     
*    CELL_4             	0.1V(5)    	Value based on 3d and 4th PIN_VOLTAGE    
*    CELL_5             	0.1V(5)    	Value based on 4th and 5th PIN_VOLTAGE   
*    CELL_6             	0.1V(5)    	Value based on 5th and 6th PIN_VOLTAGE   
*    CELL_MIN           	0.1V(5)    	Value based on CELL_1 ... CELL_6         
*    CELL_TOT           	0.1V(5)    	Value based on VOLT1...VOLT6             
*    PPM                         		Value set by Tx to control some functions (sensitivity, ...) (range is normally -100 / +100)
*    GPS_COURSE        		0.1 deg   	Orientation of plane       
*    GPS_SPEED         		0.1 km/h  	Ground speed (2D or 3D)       
*    GPS_ALTITUDE      		m         	Absolute Altitude       
*    GPS_DISTANCE      		m         	Distance from home
*    GPS_BEARING       		0.1 deg   	Direction from home  
*    TEST_1                      		Value used for test
*    TEST_2                      		Value used for test
*    TEST_3                      		Value used for test
*   (5) Les unité dependes des parametres utiliser (exemple quand une tension est fournit par un capteur de temperature, l'unité peux etre en degrées)
*       Quand mesuré des cellule d'accu, vous devez vous sassuré que la calibration doit etre en milliVoltc(OXS vas covertir les mVolt en 0.1Volt quand c'est transmi en protocole Multiplex).
***** 2.4 - données Jeti ************************************************************************************************************************
*     Les mesure transmise automatiquement sont : 
*         - Altitude relative(cm), Vitesse vertical principale(cm/sec) (si au minimum un capteur barométrique est connecté) et l'altitude maximum
*         - Tensions des cellules (si NUMBER_OF_CELLS > 0)
*         - Courant (quand un capteur de courant est connecté)
*         - GPS (long, lat, vitesse, altitude , course) (quand un GPS est connecté)
*      A ceci vous pouvez aussi specifie l'envoie de:
*         - une des six tension (si la tension est mesurer); quand un capteur NTS est utilise pour mesurer une température, il faux definir aussi un VOLTAGE_SOURCE (voir la section a propot des capteurs NTC)
*         - une température: vous pouver sélèctioner la température fourni par le MS5611 ou une sonde NTC.
*      d'autre champs peuve etre ajouté a la demande plus tard.
//#define VOLTAGE_SOURCE   VOLT_1                 // selectionné une valeur parmi: VOLT_1, VOLT_2, VOLT_3 , VOLT_4, VOLT_5 , VOLT_6
//#define TEMPERATURE_SOURCE MS5611               // selectionné une valeur parmi: MS5611 and NTC
****** 2.5 - comment renseigné TEST_1, TEST_2, TEST_3  ******    
*   OXS peux calculer plus de mesure que prévu par les protocole.
*   Quelque une d'entre elle peuve etre directement configurer voir dans les section 2.1 à 2.4 (exemple VOLT_3 peux être transmit dans T1 (pour le protocol SPORT)
*   Certaine autre sont raremenr utiliser et requiere de procédé en deux étapes;
*   - Première étape, décidé quelle mesure vonts remplir les champs TEST_1, TEST_2, TEST_3 (dans la section 2.5)
*   - Second étape, decidé dans quelle parametre de télémetry ces mesure seront envoyer (dans la section 2.1 to 2.4)
*   Pour choisir cooment ces paramètre TEST_1, TEST_2, TEST_3 doivent être remplie décomenter un ou plusieur ligne ci-dessous.
*   Si vous dé commenté plusieur ligne, prenez garde a ne pas utilisé plusieur fois le même parametre.
**************************************************************************************************************************   
//#define FILL_TEST_3_WITH_EXPECTED_ALT                        	// Dé commenté cette ligne si OXS doit calculer une altitude souhaité basé sur l'altitude actuel, Vitesse vertical et acceleration verticale
//#define EXPECTED_ALT_AT_SEC 0.2                               // temps (en sec) pour l'altitude souhaité (Cette ligne doit etre dé commenter si la précedente est dé commenté)
//#define FILL_TEST_1_2_3_WITH_LINEAR_ACC                     	// Dé commenté cette ligne si OXS doit replire les parametres TEST_1, TEST_2, TEST_3 avec l'acceleration lineaire
//#define FILL_TEST_1_2_WITH_VSPEED_AND_ALT_FROM_SECOND_VARIO  	// Dé commenté pour activé cette option
//#define FILL_TEST_1_WITH_DTE                                 	// Dé commenté pour activé cette option
//#define FILL_TEST_2_WITH_PPM_AIRSPEED_COMPENSATION           	// Dé commenté pour activé cette option
//#define FILL_TEST_1_WITH_YAWRATE                             	// Dé commenté pour activé cette option
//#define FILL_TEST1_WITH_HEADING_FROM_MAGNETOMETER             // Dé commenté pour activé cette option
//#define FILL_TEST_3_WITH_FLOW_SENSOR_CONSUMPTION             	// Dé commenté pour activé cette option
************************************************************************************************************************



**** 3 - PPM settings **************************************************************************************************
*   OXS peux (option) changer certain parameter et/ou rester certain donner a partir d'action sur l'émmeteur
*   Pour tous les protocole, cela peux etre réaliser a partir du sortie servo du recepteur pour recevoir les informations de l'émetteur.
*   Cette fonction permet depuis l’émetteur:
*      - de changer la sensibilité du vario en utilisant ou un potard ou un interrupteur de votre émetteur.
*      - de changer entre un vario compenser et non compenser (quand on utilisant 2 capteurs barométrique avec un connecté sur une sonde TEK)
*      - de réinitialiser le capteur de vitesse (quand la valeur décale avec la température)
*      - de changer le facteur de compensation du vario (quand le vario compensé utilise le capteur de vitesse) en utilisant un potentiomètre ou un interrupteur de l’émetteur.
*   Ces différentes fonctions demandent des mixages dans l’émetteur et certaine configuration dans le fichier oXs-config.h (voir ci-dessous).
*
*   Si vous voulez ces fonctions vous devez;
*      - vous devez dé commenter (en suppriment les // devant la ligne) les 3 lignes suivantes
*      - Spécifié à la ligne PIN_PPM, la PIN Arduino qui sera connecté à la sortie servo du récepteur
*            Par défaut: 2 ; vous pouvez aussi connecter la PIN 3 pour lire le signal PPM.
*            Fait bien attention d’utiliser la pine sélectionné (2 ou 3) uniquement pour le signal PPM.
*            Garder cette ligne commentée si vous ne voulez pas utilisé cette fonction.
*      - spécifié a la ligne PPM_MIN_100 la largeur d’impulsion (en micro seconde) quand la voie envoie la valeur “logique” = -100.
*              La valeur par défaut est 988.
*      - spécifié a la ligne PPM_PLUS_100 la largeur d’impulsion (en micro seconde) quand la voie envoie la valeur “logique” = +100.
*              La valeur par défaut est 2012.
*   Les deux dernières valeurs sont utilisées afin de calibrer oXs avec l’émetteur quand la fonction PPM est utilisée
*   Il est probable que si vous utilisez les valeurs par défaut cela fonctionne.
*   Il est plus sûr pour le bon fonctionnement de calibrer ces paramètres (uniquement si vous utilisé la fonction PPM).
*   /!\ TRADUCTION A REVOIR :To do so, ensure that you transmit the OXS measurement field "PPM" to the TX (e.g. as T1).
*   /!\ TRADUCTION A REVOIR :Note the values on TX (e.g. in field T1) when the TX send respectively -100 and +100 on the PPM channel (use a switch or a pot).
*   /!\ TRADUCTION A REVOIR :Fill in those values in those parameters and reload your program in the Arduino.
*
*   Si vous utilisé le protocol FRSKY SPORT (uniquement pour récepteur X) avec openTX 2.2(ou dessus) vous pouvez envoyer le signale PPM sans avoir a connecté une sortie servo du récèpteur.
*   OpenTx 2.2 vous permet de lancé un script LUA qui vous permet d'envoyer des valeur depuis votre émeteur vers OXS
*   Pour activé cette option vous devez:
*     - dé commenté la ligne #define PPM_VIA_SPORT
*     - lancer le script LUA qui vous perment d'envoyer via le protocol SPORT le même type de valeur qu une voie due recepteur. (cette valeur est comprise entre -100 and 100)
*       Ce script LUA doit utilisé une commande comme ceci: 
*            local ret = sportTelemetryPush( 0x0D , 0x10 , 0x0010 , -52 )
*       ou    
*          - 0xOD : est le numero d'identification utilisé (defini dans les fichier oXs_config_advanced.h)
*          - 0x10 : est une valuer non utilisé
*          - 0x0010 : est le code utiliser pour identifier qui s'agit d'une valeur PPM
*          - -52 : est la valeur PPM transmise (-52 est juste un exemple; elle doit etre adapter selon la valeur que on veux transmetre) 
*      vous pouvez trouvé un exemple de script LUA dans ce package (dans le dossier "lua scripts"). le nom du fichié est Name is oxsppm.lua et doit etre instaler dans le répertoire SCRIPTS/FUNCTIONS de la carte SD.
************************************************************************************************************************
#define PIN_PPM             2 
#define PPM_MIN_100       988   
#define PPM_PLUS_100      2012   


#define PPM_VIA_SPORT             // dé commenté cette ligne pour recevoir un signal PPM par le protocol SPORT a la place d'une sortie servo du récepteur (Cela nécésite un émeteur equiper d'openTX et contenant le script en LUA)

**** 4 - Reglage du vario ************************************************************************************************
*
* 4.1 - Connecting 1 or 2 barometric sensor(s) (optional feature) *********************************************
*     OXS peux etre connecter avec different capteur barometrique.
*     les meilleur resultat sont obtenu avec un capteur barometrique MS5611. Ce type de capteur est generalement monter sur une platine (comme la GY-63 ou GY-86) avec un régulateur de tension de 3.3 volt et un bus I2C.
*     Il est possible d’utiliser des platines avec des capteurs BMP085 ou BMP180 ou BMP280 (qui sont plus économiques mais mois précis). Il est à noter que les capteurs BMP085, BMP180 ou BMP280 ne peuvent être utilisé pour le premier capteur.
 Il est possible de connecter 1 ou 2 capteur barométrique ; le premier peux être un capteur de type BMP085 ou BMP180 ou BMP280 ou encore un MS5611; le second capteur doit etre un MS5611 (car les capteurs de type BMPxxx ont qu’une adresse I2C).
*         Note : Toujours utilisé un capteur qui possède un régulateur de tension 3,3Volt et un bus I2C quand on utilise le 5 Volt Vcc de l’Arduino.
*     Chaque capteur peut calculer l’altitude absolue ou relative (en mètre avec 1 décimal) et la vitesse verticale (en mètre/seconde avec 2 décimal)
*     Un second capteur peur être utile associé à une sonde TEK et si l’option PPM est active, il est possible de sélectionner depuis l’émetteur le capteur qui vas générer le sont du vario.
*     Ceci permet de basculer entre un vario compensé pneumatique ou un vario non compensé.
*     Quand on utilise deux capteur barométrique, oXs peux transmettre une valeur moyen de vitesse vertical des deux capteurs. Ceci ne semble pas très utile.
*     Vous devez specifier quelle type de capteur est utiliser pour le premier vario avec la ligne #define FIRST_BARO_SENSOR_USE     MS5611         
*        La valeur a renseigner doit etre une valeur de la liste suivante: NO_BARO , MS5611, GY86 , BMP085 , BMP180 , BMP280  
*     Vous devez spécifier quelle type de capteur est utiliser pour le second vario avec la ligne #define SECOND_BARO_SENSOR_USE     NO_BARO         
*        La valeur a renseigner doit etre une valeur de la liste suivante: NO_BARO , MS5611  
*     Les deux capteurs sont connecté en parallèle (utilise les pines A4 et A5 Arduino).
*     Le premier capteur (MS5611 ou BMPxxx) répond sur l’adresse 0x77 du bus I2C.
*			/!\ ATTENTION ne pas oublier de connecté la PIN SDO à VDD sur le BMP280 pour obtenir l'adresse 0x77
*     Si il est utilisé, le second capteur (un MS5611) doit avoir la PIN CE connecter à VDD. Comme cela l’adresse I2C sera 0x76. (Note: par défaut la pine CE du MS5611 doit être connecter a GND ainsi son adresse I2C est 0x77)
*     Note : Quand un seul capteur est connecté il doit être connecté comme premier capteur.
***********************************************************************************************************************
* 4.2 - Type de vitesse verticale transmise  *****                                    
*     Selon vos option d'implementation, OXS est capable de caluler different type de vitesse vertical et choisier la quelle doit etre transmise.
*     Selon le contenu de la ligne #define VSPEED_SOURCE, la vitesse verticale ser basé sur 
*      - premier capteur barométrique (= cas normal)
*      - deuxième capteur barométrique
*      - moyenne des deux capteur barométrique
*      - premier capteur barométrique et compensation par le tube de place (= dtE)
*      - premier capteur barométrique + IMU (accelerometer + gyroscope)
*      - premier ou second capteur barometrique selectioner par le signal PPM
***********************************************************************************************************************     
#define VSPEED_SOURCE  FIRST_BARO     // select between FIRST_BARO, SECOND_BARO , AVERAGE_FIRST_SECOND, AIRSPEED_COMPENSATED , BARO_AND_IMU or PPM_SELECTION
***********************************************************************************************************************
* 4.3 - Définition de la sensibilité par programmation *****************************
*     Quand un vario est utilisé, oXs peux prendre certain paramètres en compte pour ajuster la sensibilité 
*     La sensibilité peux être régler entre les valeurs:
*         - 20 (réglage conservatif, temps de réaction = plusieurs second)                   
*         - 150 (rapide mais beaucoup d’erreur, temps de réaction = bien inferieur a la second)       
*        50 est une valeur de réglage pour mesurer de petite vitesse vertical (recherché d’ascendance en planeur); ce réglage donne une réaction autour de la seconde.
*     la sensibilité peux être régler par programmation et/ou par l’émetteur.
*     
*     Si vous voulez une réponse très rapide du vario la meilleur solution est d’utilisé un capteur MPU6050 (accéléromètre/gyroscope) en complément du capteur barométrique (voir ci-dessous).
*     Note: Quand le vario est utilisé (#define VARIO dé commenter), vous avez a spécifié (dans la section 9) comment la vitesse vertical est calculer.
*
*     Le réglage de la sensibilité utilise 4 paramètres:
*        SENSIVITY_MIN = Cette sensibilité est la sensibilité basic du vario.
*                        Ce paramètres est donc le paramètres principale du control de sensibilité du vario.
*                        Cette valeur est utilisé par oXs quand la différence entre la valeur de la Vitesse vertical actuel (calculer toute les 20 ms) et la précédente valeur de la vitesse vertical est inferieur a la valeur définit par SENSITIVITY_MIN_AT ; la valeur typique est 40.
*        SENSIVITY_MAX = c’est la sensibilité maximal utiliser quand la vitesse vertical change très rapidement. 
*                        Cette valeur est utilisé par oXs quand la différence entre la valeur de la Vitesse vertical actuel et la précédente valeur de la vitesse vertical est supérieur a la valeur définit par SENSITIVITY_MAX_AT ; la valeur typique est 300.
*        SENSITIVITY_MIN_AT = définie jusqu’à quelle valeur de SENSITIVITY_MIN est applicable (voir ci-dessus) (cm/s); la valeur typique est 100 (cm/s).
*        SENSITIVITY_MAX_AT = définie jusqu’à quelle valeur de SENSITIVITY_MAX est applicable (voir ci-dessus) (cm/s); la valeur typique est 1000 (cm/s).
*           La sensibilité du vario est une interpolation automatique entre SENSITIVITY_MIN et SENSITIVITY_MAX.
*     Ces paramètres permettent à oXs d’avoir un temps de réaction rapide quand la vitesse verticale change rapidement et d’avoir un vario silencieux dans des condition calme.
*     Note: SENSITIVITY_MAX peut-être égale au paramètre SENSITIVITY_MIN si aucun adaptation automatique est désiré en cas de changement rapide. 
************************************************************************************************************************
#define SENSITIVITY_MIN 50
#define SENSITIVITY_MAX 300
#define SENSITIVITY_MIN_AT 100
#define SENSITIVITY_MAX_AT 1000
************************************************************************************************************************
* 4.4 - Sensitivity adjusted from the TX *******************************************************************************
*     la sensibilité peux être ajusté depuis l’émetteur grâce a un interrupteur ou un potentiomètre et quelque mixage sur un sorti servo du récepteur.    
*     Pour utilizer cette option, une sortie servo doit etre connecter à oXs (voir « Définition du retour émetteur » dans la section 3)
*     Quand oXs reçoit un signal de l’émetteur, la valeur SENSIVITY_MIN définie dans la section 4.3 est supprimer et remplacer par la valeur calculer basée sur la valeur défini dans cette section et le signal PPM de l’émetteur.
*
*     Le réglage utilise 4 parametres:
*         SENSITIVITY_MIN_AT_PPM = quand l’émetteur envoi cette valeur sur la sortie PPM, le paramètre SENSITIVITY_MIN (voir section 4.2) vas être remplacé par la valeur du paramètre SENSITIVITY_PPM_MIN;  Une valeur typique peux être 10.
*         SENSITIVITY_MAX_AT_PPM  = quand l’émetteur envoi cette valeur sur la sortie PPM, le paramètre SENSITIVITY_MIN (voir section 4.2) vas être remplacé par la valeur du paramètre SENSITIVITY_PPM_MAX;  Une valeur typique peux être 40.
*              Le paramètre SENSIVITY_PPM_MIN+MAX définie la plage dans laquelle vous aller pouvoir ajuster la sensibilité:
*         SENSITIVITY_PPM_MIN     =  valeur minimume pour le parametre SENSITIVITY_MIN qui peu lui être asigné par PPM; Une valeur typique peux être 20.
*         SENSITIVITY_PPM_MAX     =  valeur maximum pour le parameter SENSITIVITY_MIN qui peu lui être asigné par PPM; Une valeur typique peux être 100.
*             SENSITIVITY_MIN iest automatiquement interpoler entre le parametre SENSITIVITY_PPM_MIN et le parametre SENSITIVITY_PPM_MAX selon le signal PPM recu.
*     la sensibiliter ser changer seleument si la valeur du signal PMM est comprise entre SENSITIVITY_MIN_AT_PPM - 5 et SENSITIVITY_MAX_AT_PPM + 5.
*     /!\ note importante: la sensibilier est changer baser sur la valeur absolue du signal PPM; donc PPM = -25 a le même effet que PPM = 25.
*     Ceci est important pour combiner le chamgement de semcibiliter et une selection du capteur barometrique 1 et 2 (ceci permet de passer d'un vario non compensé a un vario compensé.
************************************************************************************************************************
#define SENSITIVITY_MIN_AT_PPM 10
#define SENSITIVITY_MAX_AT_PPM 40
#define SENSITIVITY_PPM_MIN  20
#define SENSITIVITY_PPM_MAX 100
************************************************************************************************************************
* 4.5 - parametre hysteresys et compensation de l'altitude baser sur un capteur de temperature ***************************************************
*     OXS peux appliquer un hysteresis sur les changement de vitesse vertical.
*     Ceci permet d'envoyer tros souvent un changement de vitesse vertical (ce qui peu en decouler de fausse alerte sonor). C'est un autre moyen de reduire la sensibilité.
*     VARIOHYSTERESIS veux dire que la vitesse vertical change si la vitesse vertical mesurer (après filtrage) differe the la valeur précédament transmise the plus de la valeur de ce paramètre.
*     Une valeur typique peux être 5  (= 5 cm/s); 0 veux dire pas de correction hysteresis.
*
*    oXs also allows to add an extra compensation to the MS5611 sensor (not to the BMPxxx) in order to reduce the drift of altitude when the internal sensor temperature increase after power on.
*    Internal temperature of MS5611 increases by several degree when it is read by the Arduino.
*    In principe MS5611 sensor contains calibration parameters in order to compensate temperature changes.
*    Still, it seems that those parameters are not always optimal.
*    So oXs allows to apply an extra compensation for the temperature. Therefore you must use fill the parameter ALT_TEMP_COMPENSATION.
*    In order to define the optimal value for your sensor, the easiest way is probably to try several values.
*    Following info can be useful:
*        - It is better to make the tests when the atmospheric pressure is stable (calm day, no wind)
*        - Ensure that altitude is displayed on the Tx
*        - Ensure that MS5611 is protected from light (because the sensor is light sensitive)
*        - First with ALT_TEMP_COMPENSATION set to zero (or the line being as comment), start Tx and Rx. Do not move oXs (so the altitude on Tx should ideally remains 0).
*        - After about 5 minutes, notice the altitude drift.
*        - Power Tx and Rx off for at least 5 min in order to let drop the internal vario temperature.
*        - Repeat this test one or 2 times
*        - If the aftitude drift is more or less the same for each test and exceed 1 meter, it will probably be possible to reduce it filling some value in the parameter ALT_TEMP_COMPENSATION
*        - If the drift is positive, then increase ALT_TEMP_COMPENSATION otherwise decrease it; ALT_TEMP_COMPENSATION can be negative (it should be the case if the initial drift is negative).
*        - It is difficult to calculate the value to be used. On my sensor I noticed that using a value = 1000 could compensate a drift of about 3 meter but it can varies per sensor.
*        - Having filled a value in ALT_TEMP_COMPENSATION, repeat the previous tests (powering Tx and Rx, waiting 5 min, looking at the drift) and increase or decrease further more the value if required.
*    Important note: filling ALT_TEMP_COMPENSATION will not eliminate totally the drift of altitude because:
*         - it can also be the result of small variation of the atmospheric pressure (that can't be compensated)
*         - it can be generated by other factors 
*         - temperature compensation is probably not linear over the whole range of temperature and pressure
************************************************************************************************************************
#define VARIOHYSTERESIS 5

* 4.6 - Switching between different vertical speeds calculations (optional) **************************************************************
*     When you use two baro sensors or one baro sensor + one airspeed sensor (4525D0 - see section 5) or one baro sensor and one IMU, OXS can calculate several vertical speeds (or dTE).
*     When the PPM option is implemented, OXS allows to select from TX which value (Vspeed from first or second baro sensor or compensated by airspeed, ...) has to be sent as vertical speed and so will control the vario tone. 
*     This allows switching between e.g. compensated and uncompensated vario.
*     Even if OXS can calculate up to 5 vertical speeds ( FIRST_BARO, SECOND_BARO , AVERAGE_FIRST_SECOND, AIRSPEED_COMPENSATED , BARO_AND_IMU ), it is only possible to switch between 2 predefined vertical speeds.
*     To enable this feature, additional parameters are required:
*       1) Specify what are respectively the primary and the secondary vertical speeds using the lines:
*                  #define VARIO_PRIMARY       XXXXXXX  
*                  #define VARIO_SECONDARY     YYYYYYY
*                 where XXXXXX and YYYYYY are each one values selected between FIRST_BARO, SECOND_BARO , AVERAGE_FIRST_SECOND, AIRSPEED_COMPENSATED , BARO_AND_IMU 
*       2) Specify a range of PPM value that OXS has to check in order to send or the primary or the secondary vertical speed using the lines:
*                 #define SWITCH_VARIO_MIN_AT_PPM 10 
*                 #define SWITCH_VARIO_MAX_AT_PPM 90 
*             When the ABSOLUTE value of PPM is between SWITCH_VARIO_MIN_AT_PPM (typical value = 10) and SWITCH_VARIO_MAX_AT_PPM (typical value = 90),
*              - OXS will switch to the primary vertical speed IF  PPM is POSITIVE
*              - OXS will switch to the secondary vertical speed IF  PPM is NEGATIVE
*            Note: when the absolute value of PPM is outside this range, OXS will not switch from vertical speed and keep the current one.
*                  This principle allows to use a switch on TX simultaneously with a pot in order to control sensitivity or compensation.
*                  Switching from positive to negative can be achieved on openTx with a mixer using MULTIPLY by -100%.
*                  Sending a PPM value outside this range allows to instruct OXS to apply another order (e.g. reset the airspeed offset) without switching the vertical speed.
*       3) Specify in section 4.2 that the source for vertical speed is "PPM_SELECTION"             
****************************************************************************************************************************
#define VARIO_PRIMARY       AIRSPEED_COMPENSATED  // select between FIRST_BARO, SECOND_BARO , AVERAGE_FIRST_SECOND, AIRSPEED_COMPENSATED , BARO_AND_IMU
#define VARIO_SECONDARY     FIRST_BARO            // select between FIRST_BARO, SECOND_BARO , AVERAGE_FIRST_SECOND, AIRSPEED_COMPENSATED , BARO_AND_IMU
#define SWITCH_VARIO_MIN_AT_PPM 10
#define SWITCH_VARIO_MAX_AT_PPM 90

* 4.7 - Analog vertical speed (optional) ***********************************************************************************
*     OXS can also deliver the vertical speed (from sensor 1 only) as an analog signal that has to be connected to A1 or A2 on FrSky receiver:
*     This can be useful if you have a receiver that has no digital communication pin (or if it is already used by another sensor)
*     Additional Hardware (1 resistor + 1 capacitor) is required! Read the WiKi if you want to use this.
*     To activate this:
*     - uncomment the 3 following parameters
*     - define in PIN_ANALOG_VSPEED the Arduino DIGITAL pin being used (see below)
*         Default 3; The pin can only be 3 or 11 because it has to use timer 2.
*     - set the min and max limits for the vertical speed (in meter/sec)
*        - ANALOG_VSPEED_MIN value or lower will apply 0 Volt to the receiver
*        - ANALOG_VSPEED_MAX  value or higher will apply 3.2 Volt to the receiver
*************************************************************************************************************************
#define PIN_ANALOG_VSPEED   3
#define ANALOG_VSPEED_MIN -3
#define ANALOG_VSPEED_MAX  3

* 4.8  - Calculating glider ratio, average sink/climb rate ***************************************************************
*     oXs can calculate and transmit glider ratio and average sink/climb rate when airspeed and vspeed stay within some tolerances for more than X seconds (e.g 5 or 10 sec)
*     The calculated values are :
*        - enlapsed time used to calculate glider ratio and average sink/climb rate
*        - averaged sink/climb rate  ( = difference of altitude / enlapsed time )
*        - glider ratio (= distance / difference of altitude) (in fact = airspeed * enlapsed time / difference of altitude )
*     Glider ratio is a parameter that can be use e.g. to fine tune the setup of the glider. It makes only sense if the speeds are quite regular.
*     So oXs calculates only when:      
*         - the airspeed does not change by more than a defined % (compared to the beginning of the enlapsed time). This % can be defined by the user in SPEED_TOLERANCE.
*         - the vertical speed stays withing a range of value defined by the user in VSPEED_MIN_TOLERANCE  and VSPEED_MAX_TOLERANCE
*     Every 0.5 sec, oXs checks if the current measurements are within the tolerance. 
*     If oXs is out of tolerance, it resets all calculations using the last (=current) measurements as new references. Glider ratio and average sink/climb are set to 0 
*     If oXs is within tolerance since more than a user defined enlapsed time (defined by GLIDER_RATIO_CALCULATED_AFTER_X_SEC), it performs the calculations
*     Note: in this version of oXs, if you want to sent the calculated field you have to fill the data to transmit section using following code
*         - TEST1 for enlapsed time (in 1/10 of sec) 
*         - TEST2 for averageVspeed (in cm/sec like Vspeed)
*         - TEST3 for gliderRatio (in 1/10 of units)
*     Glider ratio requires an airspeed sensor and a vario; 
*     Averaged sink/climb rate can be calculated even without an airspeed (but in this case tolerance on airspeed is discarded)
*     In order to activate the calculations, you must uncomment the 4 lines of parameters    
*     In order to deactivate the calculation, it is enough to put the line GLIDER_RATIO_CALCULATED_AFTER_X_SEC as comment
*************************************************************************************************************************
#define GLIDER_RATIO_CALCULATED_AFTER_X_SEC       10        // minimum elapsed time (in sec) to transmit calculations
#define SPEED_TOLERANCE              5                      // in % of speed
#define VSPEED_MIN_TOLERANCE -200                           // out of tolerance when Vspeed is lower than this value (cm/sec)
#define VSPEED_MAX_TOLERANCE  -10                           // out of tolerance when Vspeed is upper than this value (cm/sec)


************************************************************************************************************************
* Note : it is not required to comment the sensitivity, hysteresis, OutputClimbRateMin/Max, ... parameters when a vario,
*        is not used (those parameters are just discarded)
*        The vario setup parameters (sensitivity, hysteresis, PPM, ...) are shared by both baro sensors
************************************************************************************************************************