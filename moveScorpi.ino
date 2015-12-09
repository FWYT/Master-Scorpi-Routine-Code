
// jbern_experiment.ino
// 11/25/2015

// // Results/Knowledge
// - Baud rate key: {0: 9600, 1: 57600, 2: 115200, 3: 1Mbps}
// - This code has been observed to either (i) works perfectly, or (ii) be unable to write or read Dxl's ID and baud rate.
//   Solution observed to work: Power cycle the servo (unplug and plug back in).
// - Red blinking light on servo means it's not getting enough power.  Tech support says this is bad for the servos.

// // TODO
// - When you change the servo ID, does the baud rate become 3:1Mbps? (NOTE: I think it does, but haven't confirmed).
// - Write a function to reset a servo with a messed up baud rate and/or id that tries every baud rate, sets the id/baud rate to the defaults, notifies you it's done, and proves that it was successful.
// - Get RoboPlus Dynamixiel Wizard working/recognizing the OpenCM board and the XL-320's.
//   NOTE: To do this you need to load l_DxlTosser onto the OpenCM board before you start RoboPlus.
//         The tech support lady seemed a little unclear on whether this would make your board unable to control motors unless you restored the firmware or something.
//         I wouldn't try it without having tech support on the phone and/or a spare board on hand.
// - Can we set baud rate using BROADCAST_ID?  (Probably, just haven't tried.)

// // Misc Best Practices/Voodoo
// - Let's use 3:1Mps as our goto baud rate until we find a reason not to.
// - Always have batteries charged (LED _off_) before use.
// - If driving a servo, always have batteries attached and switch set to "+".
// - Try to avoid driving the motors excessively to avoid wearing down the gears.
// - When in doubt power cycle.
// - Save before downloading to the board

// // Misc References
// NOTE: Actually copy and paste links, OpenCM IDE messes up opening links somehow. :\
// - Looks real useful: http://www.robotsource.org/bs/bd.php?bt=forum_CM9DeveloperWorld&bt_id=662
// - Worrisome: http://forums.trossenrobotics.com/showthread.php?7557-Darwin-Mini-OpenCM-9-04-power-on-trouble

#define DXL_BUS_SERIAL1 1  //Dynamixel on Serial1(USART1)  <-OpenCM9.04
#define ID_NUM BROADCAST_ID

// BEGIN CONTROL TABLE DEFINES
// NOTE: These are constants for using write/readByte
// NOTE: See: http://support.robotis.com/en/product/dynamixel/xl-series/xl-320.htm
#define LED 25
#define ID 3
#define BAUD_RATE 4
// END CONTROL TABLE DEFINES

// Goal: Let's set the ID's to 1 and the BR's (baud rates) to 3.
#define DEFAULT_ID 1
#define DEFAULT_BR 3

Dynamixel Dxl(DXL_BUS_SERIAL1);
/*
//most successful sequence
double scorpi[15][15] =
{
{10.436836, 7.592069, 8.144543, 7.437668, 6.13389, 8.185085, 11.655756, 18.534516, 20.398375, 12.964144, 11.25399, 11.737859, 8.929268, 85.942316, 16.398406},
{25.455062, -32.612401, 11.112594, 9.226246, 7.873015, 10.057429, 11.791794, 13.664116, 7.796328, 4.590395, 1.02467, 0.182143, 2.257567, 8.680396, 12.835691},
{0.439625, -1.123079, 0.741419, 1.604454, 1.979324, 0.124486, -1.319513, 38.833399, -28.647881, -12.149986, -9.853317, -5.235391, 0.426017, 1.484398, 2.39299},
{-3.064829, -3.845307, -1.377899, -0.436508, 1.249068, 0.545069, 0.071643, 0.133875, -2.236866, 0.460063, -28.647867, 30.391311, 11.207474, 4.501319, -0.366064},
{-8.721245, -10.899071, -15.438098, -21.992187, 37.279971, -7.470168, -5.039325, -1.851441, -1.796328, -7.904335, -15.618395, -13.165014, -6.825627, -7.045764, -5.429212},
{14.519304, 14.17757, 13.362314, 11.483103, 10.148299, 8.102777, 5.714185, 4.724544, 3.723424, -0.062285, -1.873289, -5.105505, -10.469892, -23.060003, 14.581344},
{-9.840245, -43.228975, -10.116028, -9.962851, -9.957136, -9.6277, -9.989444, -10.077266, -12.713692, -11.342925, -10.03263, -10.139682, -13.366024, -13.412754, -14.455035},
{-6.044569, -5.009247, -4.93513, -4.145954, -3.610768, -3.762765, -4.62098, -9.90161, -38.343055, -10.625199, -12.272488, -9.574365, -8.263147, -7.441456, -7.086274},
{8.859877, 8.072451, 7.206739, 6.255109, 4.960823, 3.860391, 2.407165, 2.564431, 4.109061, 3.5, 3.094746, 42.10191, 7.927315,  11.193918, 10.015124},
{-13.573557, -13.206438, -11.730332, -10.088904, -41.483781, -8.484966, -8.305087, -9.754154, -10.326958, -8.702572, -7.909126, -10.343854, -13.40036, -13.11919, -14.721459},
{3.374723, 2.641878, -2.108253, -4.935511, -5.637288, -1.419526, 3.392962, 7.464971, 4.371741, -5.290176, -13.073845, -13.496951, -6.341956, -5.023593, -4.737788},
{-16.624445, 6.018681, 33.967693, 30.918755, 27.964058, 25.585676, 23.805518, 27.158465, 26.759461, 14.723754, 10.423433, 4.757746, -5.553141, -9.892532, -13.801719},
{-8.52322, -12.922786, -13.391469, -18.241538, -23.089584, -26.605096, -28.907106, 5.016303, 30.01262, 27.552892, 30.743056, 29.546297, 18.360107, 8.970462, -0.83435},
{-10.907219, -8.682588, -6.062592, -0.470312, 4.443187, 5.704666, 5.3184, -1.893509, -1.148829, 19.634653, -6.58185, -25.135591, -19.962493, -16.913191, -13.247964},
{18.158575, 19.942385, 20.011402, 21.911191, -1.041812, -30.377935, -30.008678, -34.956648, -34.554925, -20.767611, -16.882255, -12.400337, -0.023758, 7.680358, 14.311604}
};*/

double scorpi[15][15] =
{
{10.436836, 7.592069, 8.144543, 7.437668, 6.13389, 8.185085, 11.655756, 18.534516, 20.398375, 12.964144, 11.25399, 11.737859, 8.929268, 85.942316, 16.398406},
{25.455062, -32.612401, 11.112594, 9.226246, 7.873015, 10.057429, 11.791794, 13.664116, 7.796328, 4.590395, 1.02467, 0.182143, 2.257567, 8.680396, 12.835691},
{0.439625, -1.123079, 0.741419, 1.604454, 1.979324, 0.124486, -1.319513, 38.833399, -28.647881, -12.149986, -9.853317, -5.235391, 0.426017, 1.484398, 2.39299},
{-3.064829, -3.845307, -1.377899, -0.436508, 1.249068, 0.545069, 0.071643, 0.133875, -2.236866, 0.460063, -28.647867, 30.391311, 11.207474, 4.501319, -0.366064},
{-8.721245, -10.899071, -15.438098, -21.992187, 37.279971, -7.470168, -5.039325, -1.851441, -1.796328, -7.904335, -15.618395, -13.165014, -6.825627, -7.045764, -5.429212},
{14.519304, 14.17757, 13.362314, 11.483103, 10.148299, 8.102777, 5.714185, 4.724544, 3.723424, -0.062285, -1.873289, -5.105505, -10.469892, -23.060003, 14.581344},
{-9.840245, -43.228975, -10.116028, -9.962851, -9.957136, -9.6277, -9.989444, -10.077266, -12.713692, -11.342925, -10.03263, -10.139682, -13.366024, -13.412754, -14.455035},
{-6.044569, -5.009247, -4.93513, -4.145954, -3.610768, -3.762765, -4.62098, -38.343055, -10.625199, -12.272488, -9.90161, -9.574365, -8.263147, -7.441456, -7.086274},
{8.859877, 8.072451, 7.206739, 6.255109, 4.960823, 3.860391, 2.407165, 2.564431, 4.109061, 3.094746, 42.10191, 7.927315, 11.812081, 11.193918, 10.015124},
{-13.573557, -13.206438, -11.730332, -10.088904, -41.483781, -8.484966, -8.305087, -9.754154, -10.326958, -8.702572, -7.909126, -10.343854, -13.40036, -13.11919, -14.721459},
{3.374723, 2.641878, -2.108253, -4.935511, -5.637288, -1.419526, 3.392962, 7.464971, 4.371741, -5.290176, -13.073845, -13.496951, -6.341956, -5.023593, -4.737788},
{-16.624445, 6.018681, 33.967693, 30.918755, 27.964058, 25.585676, 23.805518, 27.158465, 26.759461, 14.723754, 10.423433, 4.757746, -5.553141, -9.892532, -13.801719},
{-8.52322, -12.922786, -13.391469, -18.241538, -23.089584, -26.605096, -28.907106, 5.016303, 30.01262, 27.552892, 30.743056, 29.546297, 18.360107, 8.970462, -0.83435},
{-10.907219, -8.682588, -6.062592, -0.470312, 4.443187, 5.704666, 5.3184, -1.893509, -1.148829, 19.634653, -6.58185, -25.135591, -19.962493, -16.913191, -13.247964},
{18.158575, 19.942385, 20.011402, 21.911191, -1.041812, -30.377935, -30.008678, -34.956648, -34.554925, -20.767611, -16.882255, -12.400337, -0.023758, 7.680358, 14.311604}
};

double scorpi_side[15][15] = //left
{
{-2.385848, -1.889585, 0.129879, 0.542476, 0.23898, 3.585353, 10.043805, 14.560866, 16.033083, 11.97257, 4.299919, 0.069267, 1.692561, 72.620616, 5.528309},
{-6.59815, -49.505031, 18.875265, 16.146481, 13.603482, 15.520393, 17.958038, 17.056822, 6.653308, -3.961835, -7.292019, -8.377642, -10.171221, -7.250729, -9.586947},
{5.722204, 5.103836, 6.280415, 6.096653, 5.12227, 2.883304, -0.58373, 40.956388, -28.635283, -10.907199, -4.291426, 0.494403, 6.026035, 7.990395, 7.510057},
{-5.8774, -6.311162, -6.659921, -6.925836, -4.910305, -3.593866, -0.124068, 3.396106, 11.196663, 40.149077, -28.647889, 3.518123, -4.608272, -6.986027, -7.033926},
{-9.028043, -13.191248, -19.18161, -22.433488, 48.821284, 4.186131, 2.302934, 2.384327, 1.203348, -7.017973, -14.692217, -11.258054, -2.422528, -2.703989, -2.586107},
{-5.313881, -4.679203, -5.197005, -5.09888, -4.162314, -4.055888, -4.074249, -4.582896, -4.267117, -7.929874, -10.153009, -10.02115, -11.145717, -51.961069, -10.817613},
{4.22098, -34.276877, -13.015393, -13.099434, -13.108952, -11.624847, -10.227019, -9.162207, -8.641302, -0.624656, 4.664753, 4.881312, 0.606801, -0.311398, 0.762613},
{-0.099305, 2.203154, 3.720131, 4.962061, 6.070797, 5.964844, 4.850627, -33.118655, -5.512799, -2.983819, 0.428313, 0.125194, -3.200386, -4.822605, -2.968499},
{-5.996254, -3.912736, -1.851248, -0.528312, -0.185114, 0.014889, 0.050208, 0.622787, 2.413169, -1.115008, 36.392489, -8.413702, -8.306685, -9.724841, -7.640833},
{-13.962915, -14.0779, -13.165376, -12.80894, -34.888316, 7.916918, 10.713325, 9.663984, 4.159201, -5.024547, -7.912799, -11.21276, -14.191601, -13.147535, -15.133603},
{22.768877, 17.436045, 12.153733, 8.867756, 6.023168, 6.26351, 9.282964, 7.698171, -6.813556, -34.269568, -41.398705, -40.366941, -33.906932, 0.912343, 27.733889},
{-22.902136, -1.9194, 6.915713, 5.890546, 5.753306, 8.226647, 14.181784, 17.475737, 19.709503, 18.357499, 7.420449, -1.887596, -6.554202, -10.51531, -14.415562},
{-1.804176, -0.600995, 1.216395, 3.135367, 8.197348, 15.961412, 28.252983, 1.481521, -5.389189, 4.665662, 10.930272, 10.442659, 0.833685, -6.618393, -3.861051},
{-2.161221, 1.342656, 4.583607, 5.487065, 4.121669, -1.569519, -9.039506, -7.796534, -0.508963, 10.51096, 4.85192, -16.383418, -12.600212, -8.881424, -5.831689},
{-4.008476, -5.794117, -7.084395, -8.023588, 0.633377, 22.118794, 7.060878, -4.679084, -13.591115, -14.241917, -11.089949, -7.983712, -2.114322, 1.520003, -1.432653}
};

double scorpi_other_side[15][15] = //right
{
{2.177704, 0.920383, -0.332002, -0.207317, 2.799214, 10.705361, 18.986939, 17.744905, 14.624365, 13.746636, 15.972391, 15.26551, -34.200634, -85.943302, -26.779786},
{31.061032, -37.929702, -3.641777, -2.33342, -2.279703, -1.307487, 1.28753, 8.052242, 8.263808, 6.241784, 3.353478, 4.188855, 9.900793, 14.519661, 16.789867},
{5.541217, -1.781824, -5.06248, -7.188334, -8.285421, -13.286574, -28.64789, 36.866543, -6.351944, -4.593977, -2.683027, 1.778928, 5.153366, 7.252317, 8.534211},
{2.665869, 0.802343, 0.893029, -0.441076, -1.03439, -3.322673, -1.70341, 3.306803, 5.22576, 6.692721, -28.645451, 40.981399, 18.575075, 10.592878, 4.648734},
{5.00791, 3.712758, 2.537287, 2.947176, 47.664436, -19.284376, -10.02557, -8.506396, -11.222695, -13.972064, -15.891387, -8.951137, -3.185472, -0.49891, 5.563166},
{-6.215999, -2.324553, -0.631131, -0.475725, -0.729685, -1.320908, 1.031911, 1.811858, 1.087744, 0.157706, -0.396796, -2.016964, 15.574984, 14.244794, 4.096662},
{-12.872061, -45.158693, -2.434706, -2.805524, -3.708439, -5.339948, -7.453764, -5.636343, -5.948247, -7.553409, -9.208066, -10.553393, -11.884553, -13.000336, -16.222259},
{-10.382794, -11.312316, -11.388453, -11.166294, -11.947218, -12.60691, -9.69301, -36.156679, 2.830775, 3.167037, 1.813753, 0.142793, -0.137372, -2.04881, -6.931824},
{10.421559, 7.792206, 6.396874, 6.172825, 6.004031, 6.979784, 8.953328, 5.762643, 2.633446, 0.640681, 40.606288, 5.588936, 12.934693, 14.09585, 13.367373},
{-1.830384, 3.704202, 6.143137, 6.879832, -33.989064, -12.317435, -14.371625, -13.482662, -11.103318, -9.007102, -7.961023, -9.957997, -9.476272, -8.531, -7.189128},
{-26.644937, -19.044575, -15.516258, -13.242038, -10.603898, -4.973802, 4.422855, 9.810402, 8.932953, 7.305306, 5.886502, 9.419163, 16.796574, -11.712179, -33.157142},
{9.588228, 7.460382, -0.589987, 0.361556, 4.359712, 13.368805, 27.362492, 26.76349, 20.825755, 15.961876, 15.266335, 11.961874, 5.662644, 3.602494, 6.371158},
{-8.869781, -8.687632, -8.669525, -9.252668, -7.962199, -4.740215, 1.207273, 15.408849, 43.455907, 35.254769, 31.983185, 23.430038, 4.903831, -6.748426, -8.962332},
{6.99793, 0.973523, -1.729821, -2.705276, -5.68435, -14.850706, -30.001446, -35.157478, -36.858066, -40.710986, -13.978083, 1.216395, 8.090805, 12.755454, 11.419405},
{1.986246, 4.123554, 5.757982, 8.597123, -6.748498, -15.592325, -24.64788, -26.229997, -24.282231, -24.192119, -26.501827, -24.281717, -12.304302, -3.394067, 0.214913}

};

double scorpi_spin[15][15] =
{
{8.961071, 5.670507, 5.111832, 5.613567, 6.358779, 11.493182, 15.34831, 15.477547, 14.05817, 13.204472, 15.099162, 17.437005, 19.342947, 84.214619, 8.263315},
{18.833902, -30.915563, 14.757807, 14.529492, 11.418243, 9.924312, 7.989332, 8.756837, 6.342782, 3.405526, 0.238456, -0.49389, 0.506987, 0.935397, 2.653557},
{0.921807, -1.767411, -1.810267, -2.436445, -3.101585, -11.060729, -28.635916, 29.893688, -16.371542, -10.274054, -8.759529, -4.866393, 0.283501, 1.881952, 2.426104},
{-2.345226, -2.01092, -0.325861, 0.267698, 2.585736, 2.718387, 5.014948, 7.807166, 7.562161, 9.43365, -28.647889, 19.71141, 0.071212, -3.584178, -4.128622},
{-11.372608, -12.075866, -13.464834, -13.24573, 43.698716, -9.434825, -6.944593, -6.88584, -9.48771, -13.531708, -17.864968, -17.242368, -15.261978, -14.580555, -8.441913},
{-2.171132, 3.380824, 4.951702, 5.11027, 5.854576, 8.181849, 13.58119, 15.6206, 14.392436, 13.314072, 13.33405, 8.950264, -1.159791, -43.090518, -11.242384},
{-11.249312, -44.624424, -10.442676, -10.687027, -10.991751, -9.696824, -8.591963, -7.574479, -8.380486, -9.184619, -10.213626, -9.356204, -8.813478, -8.811843, -11.815578},
{-6.221858, -7.659915, -9.170383, -9.559607, -9.57946, -9.34368, -5.994428, -38.957084, -7.353607, -9.1224, -9.29457, -9.125488, -8.172164, -6.460814, -5.685252},
{4.397481, 4.514877, 4.789349, 4.574262, 4.772736, 6.978023, 10.346847, 10.660678, 10.475, 9.765085, 42.435823, 9.429839, 11.474024, 10.685908, 7.703794},
{-11.521297, -10.134591, -9.110993, -8.921504, -35.450184, -10.43015, -14.475939, -15.651768, -13.932361, -11.984555, -10.378399, -11.432788, -14.364253, -15.446137, -16.132561},
{-27.416116, -4.645914, 4.545341, 7.912637, 5.348113, 5.276487, 4.129789, 2.43851, 0.367552, -3.178748, -7.678067, -12.197682, -9.831962, -42.379434, -54.796025},
{30.169645, 16.245304, -7.458522, -5.297239, -4.257378, 3.007033, 15.396687, 20.003007, 17.967736, 16.503078, 18.961731, 13.333098, -2.950659, -1.737015, 11.398658},
{6.680551, 22.55989, 30.249816, 31.837096, 35.085674, 39.967435, 45.906438, 18.894255, -13.595161, -14.220018, -11.555208, -15.728809, -31.142419, -30.66612, -17.943869},
{-1.650075, 8.833807, 12.393279, 12.693239, 11.439258, 2.090892, -8.086519, -9.009389, -4.194821, 0.262778, -31.131625, -55.428629, -46.084394, -35.938697, -22.395704},
{31.661314, 44.518402, 48.515455, 49.847882, 14.099946, -27.764205, -37.794891, -39.520773, -35.55286, -32.080166, -32.540208, -27.257535, -12.639356, -4.92945, 9.109681}
};












// Less aggressive testing function than running the servo back and forth.
// NOTE: Only works if baud rate is correct, exits with LED _off_.
void strobe_servo_led(int id) {
  for (int j = 0; j != 2; ++j) {
    for (int i = 7; i != -1; --i) {
      Dxl.writeByte(id, LED, i);
      delay(100);
    }
  }
}

//returns angle from robotis units
double getAngleForMotorPosParam(int motorParam){
  if (motorParam > 1023) motorParam = 1023;
  if (motorParam < 0) motorParam = 0;
  return motorParam / 1023.0 * 300.0 - 150.0;
}

//return robotis units from angl
int getMotorPosParamForAngle(double angle){
  if (angle < -150) angle = -150;
  if (angle > 150) angle = 150;

  return (angle + 150.0)/300.0 * 1023;
}

//given a desired velocity in degrees per second, get the corresponding motor speed parameter for the dynamixels
int getMotorSpeedParamForAngularVelocity(double angularVel){
  //max velocity (depends on Voltage :( ) is 114rpm == 684 deg/sec, and this corresponds to a value of 1023.
  if (angularVel < 0) angularVel *= -1;
  if (angularVel >= 684) return 0;

  return angularVel / 684.0 * 1022 + 1;
}

void strobe_dance() {
  int ids[12] = {2, 3, 4, 5, 7, 8, 9, 10, 12, 13, 14, 15};
  for (int i = 1; i != 13; ++i) {
    strobe_servo_led(ids[i]);
  }
}

// More aggressive testing function than running the servo back and forth.
// NOTE: Only works if baud rate is correct, exits with servo zeroed (probably).
void strobe_goal_position(int id) {
  Dxl.goalPosition(id, 1);
  delay(2000);
  Dxl.goalPosition(id, 1023);
  delay(2000);
  Dxl.goalPosition(id, 512);
  delay(2000);
}

void set_goal_position(int id, double pos) {
  Dxl.goalPosition(id, getMotorPosParamForAngle(pos));
  //delay(2000);
}

// Arguments are in degrees and degrees/sec.
void set_goal_pos_and_vel(int id, double pos, double vel) { 
  /*SerialUSB.print(id);
  SerialUSB.print(" ");
  SerialUSB.print(getMotorPosParamForAngle(pos));
  SerialUSB.print(" ");
  SerialUSB.print(getMotorSpeedParamForAngularVelocity(vel));
  SerialUSB.print(" ");
  SerialUSB.print("\n");*/
  Dxl.setPosition(id, getMotorPosParamForAngle(pos), getMotorSpeedParamForAngularVelocity(vel));
  //delay(2000);
}


// NOTE: Uses BROADCAST_ID to set.
void set_id(int id) {
    Dxl.writeByte(BROADCAST_ID, ID, id);
}

void set_br(int id, int br) {
    Dxl.writeByte(id, BAUD_RATE, br);
}

void setup_motors() {
  Dxl.jointMode(BROADCAST_ID);
  delay(1000);
}

void stand() {
  set_goal_pos_and_vel(BROADCAST_ID, 0, 90);
  delay(1500);
}

void sit()
{ 
  int t[15] = {0,0,0,0,0,-1,-1,-1,1,-1,0,0,0,0,0};
  for (int i = 0; i<15; i++) {
    set_goal_pos_and_vel(i+1, t[i]*90, 90);
  }
  
  
  delay(1500);   
  
}

void wag()
{
  int s[16] = {10, 20, 30, 40, 30, 20, 10, 0, -10, -20, -30, -40, -30, -20, -10, 0};
  int t[5] = {0,-1,1,-1,1};
  for (int k = 2; k<6; k++)
  {
    set_goal_pos_and_vel(k, 45*t[k-1], 70);
  }
  
   
  
  for (int j = 0; j<4; j++)
  {
    for (int i = 0; i<16; i++)
    {
      set_goal_pos_and_vel(11, s[i], 70);
      delay(100);
    }
  }
  delay(1500);
}

void sway() {
  double pos[12] = {10, 20, 50, 20, 10, 0, -10, -20, -50, -20, -10, 0};
  double dt = 300;
  double theta_prev = 0;
  for (int j = 0; j!=3; ++j) { //number of repetitions
    for (int n = 0; n!=12; ++n) { //number of positions for each motor
      double theta = pos[n];
      double dtheta = theta - theta_prev;
      SerialUSB.println(dtheta);
      
      for (int i=0; i!=16; i++) { //motor ids
        set_goal_pos_and_vel(i, theta, dtheta / dt * 1000);
      }
      delay(dt);
      
      theta_prev = theta;
    }
  }         
}

void sway_w_sync1() {
  double pos[12] = {10, 20, 50, 20, 10, 0, -10, -20, -50, -20, -10, 0};
  
  word sync[12][12]; //12 position values, 4 motors, each motor has 3 values (id, goal pos, goal velocity)
  int count=0;
  double dt = 300;
  double theta_prev = 0;
  
  for (int i=0; i!=12; i++) //number of position values
  {
     double theta = pos[i];
     double dtheta = theta - theta_prev;
     SerialUSB.println(dtheta);
     for (int m = 12; m!=16; m++) //motor ids
     {
       sync[i][count] = m;
       sync[i][count+1] = getMotorPosParamForAngle(theta);
       sync[i][count+2] = getMotorSpeedParamForAngularVelocity(dtheta / dt * 1000);
       count+=3;
     }
     theta_prev = theta;
     count = 0;
  }
 
  for (int c = 0; c<1; c++) //number of repetitions
  {
    for (int k = 0; k<12; k++) // number of positions
    {
      Dxl.writeByte(BROADCAST_ID, LED, k%7); //changes colors
      Dxl.syncWrite(30,2,sync[k],12);
      delay(dt); 
    }
  }
}

void walk() {
  double dt = 400;
  double theta_prev[15] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
  
  for (int j = 0; j!=10; ++j) { //number of repetitions
    for (int t = 0; t!=12; ++t) { //number of position values per motor
      //double theta = pos[t];
      //double dtheta = theta - theta_prev;
      for (int i=0; i!=15; i++) { //motor ids
        double theta = scorpi[i][t];
        double dtheta = theta - theta_prev[i];
        theta_prev[i] = dtheta;
        set_goal_pos_and_vel(i+1, theta, dtheta / dt * 1000);
      }
      delay(dt);
      
      //theta_prev = theta;
    }
  }      
}

void walk_w_sync() 
{
  double dt = 100;
  double theta_prev[15] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
  
  word sync[15][45];
  int count = 0;
  
  //set up array
  for (int i=0; i!=15; i++) //number of position values
  {
     
     //SerialUSB.println(dtheta);
     for (int m = 0; m!=16; m++) //motor ids
     {
       double theta = scorpi[m][i];
       double dtheta = theta - theta_prev[m];
       theta_prev[i] = dtheta;
       /*SerialUSB.print(m+1);
       SerialUSB.print(" ");
       SerialUSB.print(getMotorPosParamForAngle(theta));
       SerialUSB.print(" ");
       SerialUSB.print(getMotorSpeedParamForAngularVelocity(dtheta / dt * 1000));
       SerialUSB.print(" ");
       SerialUSB.print("\n");*/
       sync[i][count] = m+1;
       sync[i][count+1] = getMotorPosParamForAngle(theta);
       //sync[i][count+2] = getMotorSpeedParamForAngularVelocity(dtheta / dt * 1000);
       sync[i][count+2] = 0;
       count+=3;
     }
     count = 0;
  }
  
  
  for (int c = 0; c<4; c++) //number of repetitions
  {
    for (int k = 0; k<15; k++) // number of positions
    {
      //Dxl.writeByte(BROADCAST_ID, LED, k%7); //changes colors
      //Dxl.writeByte(BROADCAST_ID, LED, 5);
      //Dxl.writeByte(BROADCAST_ID, LED, 6);
      //delay(1000);
      Dxl.syncWrite(30,2,sync[k],45);
      delay(dt); 
      //Dxl.writeByte(BROADCAST_ID, LED, 5);
      //delay(3000);
    }
  }
  
}

void spin() 
{
  double dt = 100;
  double theta_prev[15] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
  
  word sync[15][45];
  int count = 0;
  
  //set up array
  for (int i=0; i!=15; i++) //number of position values
  {
     
     //SerialUSB.println(dtheta);
     for (int m = 0; m!=16; m++) //motor ids
     {
       double theta = scorpi_spin[m][i];
       double dtheta = theta - theta_prev[m];
       theta_prev[i] = dtheta;
       /*SerialUSB.print(m+1);
       SerialUSB.print(" ");
       SerialUSB.print(getMotorPosParamForAngle(theta));
       SerialUSB.print(" ");
       SerialUSB.print(getMotorSpeedParamForAngularVelocity(dtheta / dt * 1000));
       SerialUSB.print(" ");
       SerialUSB.print("\n");*/
       sync[i][count] = m+1;
       sync[i][count+1] = getMotorPosParamForAngle(theta);
       //sync[i][count+2] = getMotorSpeedParamForAngularVelocity(dtheta / dt * 1000);
       sync[i][count+2] = 0;
       count+=3;
     }
     count = 0;
  }
  
  
  for (int c = 0; c<15; c++) //number of repetitions
  {
    for (int k = 0; k<15; k++) // number of positions
    {
      //Dxl.writeByte(BROADCAST_ID, LED, k%7); //changes colors
      //Dxl.writeByte(BROADCAST_ID, LED, 5);
      //Dxl.writeByte(BROADCAST_ID, LED, 6);
      //delay(1000);
      Dxl.syncWrite(30,2,sync[k],45);
      delay(dt); 
      //Dxl.writeByte(BROADCAST_ID, LED, 5);
      //delay(3000);
    }
  }
  
}


void walk_sideways_w_sync(int dir) 
{
  double dt = 100;
  double theta_prev[15] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
  
  word sync[15][45];
  int count = 0;
  
  //set up array
  for (int i=0; i!=15; i++) //number of position values
  {
     double theta;
     //SerialUSB.println(dtheta);
     for (int m = 0; m!=16; m++) //motor ids
     {
       if (dir == 1)
       {
         theta = scorpi_side[m][i];
       }
       else
       {
         theta = scorpi_other_side[m][i];
       }
       double dtheta = theta - theta_prev[m];
       theta_prev[i] = dtheta;
       /*SerialUSB.print(m+1);
       SerialUSB.print(" ");
       SerialUSB.print(getMotorPosParamForAngle(theta));
       SerialUSB.print(" ");
       SerialUSB.print(getMotorSpeedParamForAngularVelocity(dtheta / dt * 1000));
       SerialUSB.print(" ");
       SerialUSB.print("\n");*/
       sync[i][count] = m+1;
       sync[i][count+1] = getMotorPosParamForAngle(theta);
       //sync[i][count+2] = getMotorSpeedParamForAngularVelocity(dtheta / dt * 1000);
       sync[i][count+2] = 0;
       count+=3;
     }
     count = 0;
  }
  
  
    
  
  
  for (int c = 0; c<4; c++) //number of repetitions
  {
    for (int k = 0; k<15; k++) // number of positions
    {
      //Dxl.writeByte(BROADCAST_ID, LED, k%7); //changes colors
      //Dxl.writeByte(BROADCAST_ID, LED, 5);
      //Dxl.writeByte(BROADCAST_ID, LED, 6);
      //delay(1000);
      Dxl.syncWrite(30,2,sync[k],45);
      delay(dt); 
      //Dxl.writeByte(BROADCAST_ID, LED, 5);
      //delay(3000);
    }
  }
  
}



void setup() {
  // NOTE: These delays may actually be the solution.  This is terrifying.
  delay(1000);
  Dxl.begin(3); // NOTE: Need to start this with servo's baud rate to make changes to that servo.
  delay(1000);
  
  setup_motors();
  //strobe_servo_led(BROADCAST_ID);
  
  
  stand();
  //Dxl.writeByte(BROADCAST_ID, LED, 5);
  //sway_w_sync1();
  
  

  //blink to put on cover
  for (int i=0; i<10; i++)
  {
      Dxl.writeByte(BROADCAST_ID, LED, 4);
      delay(500);
      Dxl.writeByte(BROADCAST_ID, LED, 0);
      delay(500);
      
  }
  
  //walk();
  sway_w_sync1();
  delay(1000);
  
  for (int i=1; i<6; i++)
  {
    Dxl.writeByte(i, LED, 3); //lowest motors
    Dxl.writeByte(i+5, LED, 6);
    Dxl.writeByte(i+10, LED, 5);
  }
  
  walk_sideways_w_sync(1); 
  delay(1000);
  
  //for (int i=1; i<6; i++)
  //{
   // Dxl.writeByte(i, LED, 4); //lowest motors
    //Dxl.writeByte(i+5, LED, 2);
    //Dxl.writeByte(i+10, LED, 7);
  //}
  
  walk_sideways_w_sync(0); 
  
  for (int i=1; i<6; i++)
  {
    Dxl.writeByte(i, LED, 1); //lowest motors
    Dxl.writeByte(i+5, LED, 3);
    Dxl.writeByte(i+10, LED, 4);
  }
  
  delay(1000);
  walk_w_sync();
  for (int i=1; i<6; i++)
  {
    Dxl.writeByte(i, LED, 4); //lowest motors
    Dxl.writeByte(i+5, LED, 5);
    Dxl.writeByte(i+10, LED, 6);
  }
  delay(1000);
  spin();
  delay(1000);
  
  for (int i=1; i<6; i++)
  {
    Dxl.writeByte(i, LED, 4); //lowest motors
    Dxl.writeByte(i+5, LED, 6);
    Dxl.writeByte(i+10, LED, 7);
  }
  
  sit();
  
  Dxl.writeByte(BROADCAST_ID, LED, 7);
  
  wag();
   
  //sway();
  //sway_w_sync1();
  //sway_w_sync2();
  //delay(1000);
  //slide();
  strobe_servo_led(BROADCAST_ID);
  
  // NOTE: Uncomment this to test if you have the right baud rate (uses BROADCAST_ID, so you don't have to have the id right)
  // strobe_servo_led(BROADCAST_ID);
  
  // TODO: Some code I found online has this command.  I have no idea what it does.
  //       It may come up when you want to both monitor serial _and_ drive servos?
  //Serial2.begin(9600);
  //delay(1000);

  // NOTE: These delays are more on the voodoo side.  I wouldn't remove them until we really have stuff working though.
  //int TARGET_ID = 15;
  //set_id(TARGET_ID);
  //delay(1000);
  //set_br(DEFAULT_ID, DEFAULT_BR);
  //delay(1000);
  
  //Dxl.jointMode(BROADCAST_ID);
  //strobe_servo_led(TARGET_ID);
  //strobe_dance();
  //strobe_goal_position(DEFAULT_ID);
}

void loop() {
  // Set this to 1 if you want to verify that the print calls are actually being made (will print 255 if something's wrong => try power cycling).
  int FORCE_VIEW_SERIAL = 1;
  
  // NOTE: Ctrl + Shift + M to view Serial output
  // NOTE: These will only print if you've got the baud rate and id correct everywhere (or if you've set FORCE_VIEW_SERIAL to 1).
  unsigned char id_str = Dxl.readByte(DEFAULT_ID, ID);
  unsigned char br_str = Dxl.readByte(DEFAULT_ID, BAUD_RATE);
  if (id_str != 255 || FORCE_VIEW_SERIAL) {
    SerialUSB.print("ID: ");
    SerialUSB.println(id_str);
  }
  if (br_str != 255 || FORCE_VIEW_SERIAL) {
    SerialUSB.print("Baud Rate: ");
    SerialUSB.println(br_str);
  }
}
