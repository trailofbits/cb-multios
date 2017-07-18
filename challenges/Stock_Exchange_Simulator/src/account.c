/*
 * Copyright (C) Narf Industries <info@narfindustries.com>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included
 * in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
 * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
 * CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
 * TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
 * SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

#include "cgc_libc.h"
#include "cgc_account.h"

account_record_t cgc_ACCOUNTS[NUM_ACCOUNTS];
void cgc_init_account(uint32_t idx, float balance, char *key){
    // unsafe to be called externally
    cgc_ACCOUNTS[idx].balance = balance;
	for(int i = 0; i < KEY_LEN; ++i){
		cgc_ACCOUNTS[idx].key[i] = key[i];
	}
}
option_holding_t * cgc_next_holding(uint32_t acct_id){
	for(int i = 0; i < MAX_HOLDINGS; i++){
		if(cgc_ACCOUNTS[acct_id].holdings[i].symbol[0] == 0x0)
			return &(cgc_ACCOUNTS[acct_id].holdings[i]);
	}
	return NULL;
}
void cgc_init_holding(uint32_t acct_id, uint32_t holding_idx, char *sym, uint32_t qty){
	option_holding_t *t = &(cgc_ACCOUNTS[acct_id].holdings[holding_idx]);
	t->qty = qty;
	cgc_memcpy(sym, t->symbol, cgc_strlen(sym));


}
void cgc_init_accounts(){
		
			cgc_init_account(0, 351872.0, "f97adfe8fa275092adf100d06900aed0" );


		
			cgc_init_account(1, 727435.0, "11160ee476ee4d0e967bc19123306bb6" );


		
			cgc_init_account(2, 950234.0, "0c5701cee646b0f3f87a0fe9db5a024b" );


		
			cgc_init_account(3, 179012.0, "747bcc0e0f08aefb72860b6ec9c435cc" );


		
			cgc_init_account(4, 692642.0, "e2cb96336c57f7b627157a85ed2703dd" );


		
			cgc_init_account(5, 285316.0, "ccefe6f38a3b0dc38ad5b0522eb0e029" );


		
			cgc_init_account(6, 515174.0, "1a0843b9fa65a1b261f2504c9e879f91" );


		
			cgc_init_account(7, 188301.0, "43bf8cc93f259c6c468f6f49b02f8f86" );


		
			cgc_init_account(8, 965475.0, "2d97f928e3f5147c39eddcd134675558" );


		
			cgc_init_account(9, 615249.0, "18cdc243dc965537e08908cc7740f698" );


		
			cgc_init_account(10, 831992.0, "824b37f224ed67d898cddd9144327522" );


		
			cgc_init_account(11, 985784.0, "1a5bec5a98f816d4a9e2ed5ef764ec33" );


		
			cgc_init_account(12, 407811.0, "ded4773c7efa13ca2f176735cf32f718" );


		
			cgc_init_account(13, 862651.0, "57c02d796238b4a27093332f5757dd04" );


		
			cgc_init_account(14, 895654.0, "4943cc5abda9e094a722a3127dbb9be3" );


		
			cgc_init_account(15, 740467.0, "113ac07641cb7675d2dce9bf1ccf697e" );


		
			cgc_init_account(16, 712870.0, "2306dd49e6a25060e8f8aece11173fdb" );


		
			cgc_init_account(17, 565871.0, "c122c416d1415d0cb34e9dba6dc18c87" );


		
			cgc_init_account(18, 130899.0, "f163ff8824fac3c605d53f37e5e614b9" );


		
			cgc_init_account(19, 525527.0, "7fb252b79b9d4b1c36ac952e7c647394" );


		
			cgc_init_account(20, 195627.0, "0376ec02f502a3ae1a776494f67ad2bd" );


		
			cgc_init_account(21, 30985.0, "c35b360d25bbb643a064315b05cbb761" );


		
			cgc_init_account(22, 844713.0, "ec3603d1a80fc0a9c584ee82bfc0be67" );


		
			cgc_init_account(23, 146629.0, "1500be58a39ce15068039c989a4a9caf" );


		
			cgc_init_account(24, 101628.0, "ea512ff327d39e37ddd7f5b169970469" );


		
			cgc_init_account(25, 488891.0, "019fc054eac8fb229d6f79a7e33e7ce2" );


		
			cgc_init_account(26, 565619.0, "5f8e90f5fb1f023a116032fc5aeba703" );


		
			cgc_init_account(27, 649800.0, "d722a3ddd133b5170fb6fc5bfdacdcbc" );


		
			cgc_init_account(28, 185566.0, "707bd2a4e33ca64c0bd14e8f77f1eea0" );


		
			cgc_init_account(29, 386190.0, "eeacf644840aec168a972e22ab7ed436" );


		
			cgc_init_account(30, 405717.0, "290b277185b2f6118f8748cd128b61ad" );


		
			cgc_init_account(31, 459429.0, "51174b4b91682fa90c995b29c1d122cc" );


		
			cgc_init_account(32, 716827.0, "241fe5c8bf8b3937860801e13759315b" );


		
			cgc_init_account(33, 952510.0, "e68614df50cdb2377dcd34ab21d8e6c9" );


		
			cgc_init_account(34, 21789.0, "819deb8ca551b6a9644f35750c37c231" );


		
			cgc_init_account(35, 345424.0, "fdf1252401682267f80c76625403710d" );


		
			cgc_init_account(36, 462559.0, "a8c9e2d05a8ef23cdc219d377d53e878" );


		
			cgc_init_account(37, 26141.0, "aa5e73418a4d8ebcbf4242c08c78a415" );


		
			cgc_init_account(38, 730177.0, "de153b1b106b6558dfa7260bc58525c0" );


		
			cgc_init_account(39, 89584.0, "6cad7fb4bdc6971c41b568563e048c53" );


		
			cgc_init_account(40, 606271.0, "b8809d33c0df937314815215820d9d65" );


		
			cgc_init_account(41, 496230.0, "db5adad297a95000a7da8eb236d1cfe9" );


		
			cgc_init_account(42, 134737.0, "424df7c2b9ef58790a33b52f67b5191f" );


		
			cgc_init_account(43, 61037.0, "336cfe590bd1bcd823899b14493cf23c" );


		
			cgc_init_account(44, 389370.0, "66e360b7b285f86c994233c5ab38bea5" );


		
			cgc_init_account(45, 250361.0, "56ce86e58a14fc504cf6998b870aa804" );


		
			cgc_init_account(46, 48908.0, "828606bf767986d4cc7b4ec8e9aff92a" );


		
			cgc_init_account(47, 910043.0, "7179eff9bc72122b89beff120d2c8734" );


		
			cgc_init_account(48, 681630.0, "6549b8e98be71bac2abd6996627bce4e" );


		
			cgc_init_account(49, 968739.0, "acece5019f5ed9a0cacf2e0b1d431afd" );


		
			cgc_init_account(50, 987159.0, "4d170b9c1c7031ef97163bbec3b80bbd" );


		
			cgc_init_account(51, 795609.0, "9efb58f255f7ad220640a95f2a9c77f2" );


		
			cgc_init_account(52, 933789.0, "9ef33ee3414ccd3b1eb43bc0b8ce49e2" );


		
			cgc_init_account(53, 538656.0, "34d94e3a5578082d38538c3424b77270" );


		
			cgc_init_account(54, 234549.0, "79b7fa5d363e03383f11ecdd92d97447" );


		
			cgc_init_account(55, 492490.0, "9079765c700058627dce99bafd54432a" );


		
			cgc_init_account(56, 498241.0, "ff1d7b03b27d0a6870d60f9d4795e92b" );


		
			cgc_init_account(57, 291754.0, "edb3c285ddfc94bd1afcd62832eca795" );


		
			cgc_init_account(58, 900804.0, "4ab3d2acc0ab50efa85ebf5c684bd530" );


		
			cgc_init_account(59, 817367.0, "72558d6c2d653b9082933d372ef1b269" );


		
			cgc_init_account(60, 548826.0, "a0faff8d8717d436c7e8e8f522ed1803" );


		
			cgc_init_account(61, 338763.0, "2232fd538ff3aafb810a5f688046dd17" );


		
			cgc_init_account(62, 612511.0, "6a6d931e932772b36d61ddcc41dbc221" );


		
			cgc_init_account(63, 248099.0, "ec577dba35a82e1b26f613ece6c6840d" );


		
			cgc_init_account(64, 137621.0, "2e63fb8baa93b26763b6ca1ef3c8585d" );


		
			cgc_init_account(65, 601985.0, "005b04f8c3b18b9fa4faa9b02e7baf73" );


		
			cgc_init_account(66, 895600.0, "569cadedd7e85c73126b13f6a1d227e3" );


		
			cgc_init_account(67, 813732.0, "257a1c63f6715d7fa2cb06a5650afb9f" );


		
			cgc_init_account(68, 902792.0, "03b5c42113686b52870b485d1817fd85" );


		
			cgc_init_account(69, 980637.0, "7018e4ac5d1268d370b2ca79da5057a0" );


		
			cgc_init_account(70, 717722.0, "cf643ea74cdf6b26939ee46b4625b9ea" );


		
			cgc_init_account(71, 370086.0, "ac6bf456bd7a791853878fb217774250" );


		
			cgc_init_account(72, 924122.0, "6500045faaaa7b12bef294b0f0af0a09" );


		
			cgc_init_account(73, 315510.0, "c3385a46c4adb2cdcbb1e25a3927ccb8" );


		
			cgc_init_account(74, 807525.0, "bb2404390204fe5d8beb9cd13a526e9c" );


		
			cgc_init_account(75, 755005.0, "5ab2beaec063d59802bcad0c5cd39b6d" );


		
			cgc_init_account(76, 571891.0, "1142c827f4f3cc46e08866d9e88eedd1" );


		
			cgc_init_account(77, 916740.0, "4c37e154220c50c1077493851d1011ea" );


		
			cgc_init_account(78, 261422.0, "d5a1152a053af0b1f9b387346866d5b2" );


		
			cgc_init_account(79, 672404.0, "512457dc65f54d89dc8706d032b45443" );


		
			cgc_init_account(80, 837339.0, "26127ebcfa0b1669559784ea1824d250" );


		
			cgc_init_account(81, 42721.0, "f186934fb856ca0110151ad296da653f" );


		
			cgc_init_account(82, 423199.0, "76910c570029849e0eaaa589b26e3759" );


		
			cgc_init_account(83, 774688.0, "0ef281a265db8cc1a2f26adce8f09539" );


		
			cgc_init_account(84, 844939.0, "c168709a6158047f520dd8f1442a92a0" );


		
			cgc_init_account(85, 413335.0, "d2663cd7f26b91bf2eb322e6025d1df4" );


		
			cgc_init_account(86, 310964.0, "7118b3ce1daf916b9499f69024791473" );


		
			cgc_init_account(87, 262982.0, "cc190a7badd466d6e430b2966429bcb5" );


		
			cgc_init_account(88, 121236.0, "799da893ad735b3a669e144d5aa67dab" );


		
			cgc_init_account(89, 323998.0, "2932fb4aa9794a0caf3b263659419c26" );


		
			cgc_init_account(90, 118980.0, "83796f2ba285775fc968c6061cd6a1c0" );


		
			cgc_init_account(91, 170693.0, "0ab61be15e4ae36dd434cd6f104e2fc4" );


		
			cgc_init_account(92, 313740.0, "5df66a4add8373aca93b06f6c982e0e3" );


		
			cgc_init_account(93, 332259.0, "fbc29f5043a4e28c92312f32ff687511" );


		
			cgc_init_account(94, 727311.0, "fcaf38921282e14608214823e0597e21" );


		
			cgc_init_account(95, 436214.0, "cc5bac4d6c1e3f99b99a5792f19b15b4" );


		
			cgc_init_account(96, 958360.0, "35f40bd506c8086a2569f2ca2dde1b29" );


		
			cgc_init_account(97, 46946.0, "3a37a6af6981bfa12cfae817c2231447" );


		
			cgc_init_account(98, 235512.0, "45629735ff7a20ca7c1aa375525be9e4" );


		
			cgc_init_account(99, 847132.0, "d97236f062e48047aedd7957122c8238" );


		
		
			cgc_init_holding(0, 0, "GOOG", 12697418);
		
			cgc_init_holding(0, 1, "SK3WL", 13609627);
		
			cgc_init_holding(0, 2, "NRFIN", 5962175);
		
			cgc_init_holding(0, 3, "KPRCA", 2164075);
		
			cgc_init_holding(0, 4, "AAPL", 7107186);
		
			cgc_init_holding(0, 5, "OAK", 9147668);
		
			cgc_init_holding(0, 6, "DDTEK", 4294967295);
		
			cgc_init_holding(0, 7, "PALM", 12454340);
		
			cgc_init_holding(0, 8, "CROMU", 13645664);
		
			cgc_init_holding(0, 9, "PIRATE", 9417541);
		
			cgc_init_holding(0, 10, "MAPLE", 10179641);
		
			cgc_init_holding(1, 0, "GOOG", 12929200);
		
			cgc_init_holding(1, 1, "SK3WL", 14026567);
		
			cgc_init_holding(1, 2, "NRFIN", 16257266);
		
			cgc_init_holding(1, 3, "KPRCA", 1501564);
		
			cgc_init_holding(1, 4, "AAPL", 6155379);
		
			cgc_init_holding(1, 5, "OAK", 16460465);
		
			cgc_init_holding(1, 6, "DDTEK", 4294967295);
		
			cgc_init_holding(1, 7, "PALM", 10590440);
		
			cgc_init_holding(1, 8, "CROMU", 4065689);
		
			cgc_init_holding(1, 9, "PIRATE", 12342544);
		
			cgc_init_holding(1, 10, "MAPLE", 13571855);
		
			cgc_init_holding(2, 0, "GOOG", 9562695);
		
			cgc_init_holding(2, 1, "SK3WL", 4294967295);
		
			cgc_init_holding(2, 2, "NRFIN", 8335444);
		
			cgc_init_holding(2, 3, "KPRCA", 3689543);
		
			cgc_init_holding(2, 4, "AAPL", 11318699);
		
			cgc_init_holding(2, 5, "OAK", 15206633);
		
			cgc_init_holding(2, 6, "DDTEK", 6387741);
		
			cgc_init_holding(2, 7, "PALM", 15315607);
		
			cgc_init_holding(2, 8, "CROMU", 15930862);
		
			cgc_init_holding(2, 9, "PIRATE", 1207764);
		
			cgc_init_holding(2, 10, "MAPLE", 6822811);
		
			cgc_init_holding(3, 0, "GOOG", 13230134);
		
			cgc_init_holding(3, 1, "SK3WL", 6577574);
		
			cgc_init_holding(3, 2, "NRFIN", 7860633);
		
			cgc_init_holding(3, 3, "KPRCA", 6681541);
		
			cgc_init_holding(3, 4, "AAPL", 4580790);
		
			cgc_init_holding(3, 5, "OAK", 5084198);
		
			cgc_init_holding(3, 6, "DDTEK", 4294967295);
		
			cgc_init_holding(3, 7, "PALM", 7264059);
		
			cgc_init_holding(3, 8, "CROMU", 3060599);
		
			cgc_init_holding(3, 9, "PIRATE", 4860182);
		
			cgc_init_holding(3, 10, "MAPLE", 11247052);
		
			cgc_init_holding(4, 0, "GOOG", 15570477);
		
			cgc_init_holding(4, 1, "SK3WL", 3432318);
		
			cgc_init_holding(4, 2, "NRFIN", 12741618);
		
			cgc_init_holding(4, 3, "KPRCA", 3172918);
		
			cgc_init_holding(4, 4, "AAPL", 7604478);
		
			cgc_init_holding(4, 5, "OAK", 6492051);
		
			cgc_init_holding(4, 6, "DDTEK", 6761905);
		
			cgc_init_holding(4, 7, "PALM", 4294967295);
		
			cgc_init_holding(4, 8, "CROMU", 9215083);
		
			cgc_init_holding(4, 9, "PIRATE", 11751177);
		
			cgc_init_holding(4, 10, "MAPLE", 6121063);
		
			cgc_init_holding(5, 0, "GOOG", 16767060);
		
			cgc_init_holding(5, 1, "SK3WL", 3120718);
		
			cgc_init_holding(5, 2, "NRFIN", 2222454);
		
			cgc_init_holding(5, 3, "KPRCA", 15925974);
		
			cgc_init_holding(5, 4, "AAPL", 9007607);
		
			cgc_init_holding(5, 5, "OAK", 3734544);
		
			cgc_init_holding(5, 6, "DDTEK", 4294967295);
		
			cgc_init_holding(5, 7, "PALM", 9858813);
		
			cgc_init_holding(5, 8, "CROMU", 1140598);
		
			cgc_init_holding(5, 9, "PIRATE", 14471737);
		
			cgc_init_holding(5, 10, "MAPLE", 5019638);
		
			cgc_init_holding(6, 0, "GOOG", 6875083);
		
			cgc_init_holding(6, 1, "SK3WL", 4294967295);
		
			cgc_init_holding(6, 2, "NRFIN", 10347720);
		
			cgc_init_holding(6, 3, "KPRCA", 3731967);
		
			cgc_init_holding(6, 4, "AAPL", 13351890);
		
			cgc_init_holding(6, 5, "OAK", 1050721);
		
			cgc_init_holding(6, 6, "DDTEK", 1875851);
		
			cgc_init_holding(6, 7, "PALM", 4305051);
		
			cgc_init_holding(6, 8, "CROMU", 16431291);
		
			cgc_init_holding(6, 9, "PIRATE", 15860601);
		
			cgc_init_holding(6, 10, "MAPLE", 6882954);
		
			cgc_init_holding(7, 0, "GOOG", 16635781);
		
			cgc_init_holding(7, 1, "SK3WL", 10306122);
		
			cgc_init_holding(7, 2, "NRFIN", 7533549);
		
			cgc_init_holding(7, 3, "KPRCA", 11826853);
		
			cgc_init_holding(7, 4, "AAPL", 16602355);
		
			cgc_init_holding(7, 5, "OAK", 5836793);
		
			cgc_init_holding(7, 6, "DDTEK", 4294967295);
		
			cgc_init_holding(7, 7, "PALM", 11905535);
		
			cgc_init_holding(7, 8, "CROMU", 12145804);
		
			cgc_init_holding(7, 9, "PIRATE", 13676509);
		
			cgc_init_holding(7, 10, "MAPLE", 10686102);
		
			cgc_init_holding(8, 0, "GOOG", 11880185);
		
			cgc_init_holding(8, 1, "SK3WL", 5848188);
		
			cgc_init_holding(8, 2, "NRFIN", 3691309);
		
			cgc_init_holding(8, 3, "KPRCA", 14501760);
		
			cgc_init_holding(8, 4, "AAPL", 12428824);
		
			cgc_init_holding(8, 5, "OAK", 4757678);
		
			cgc_init_holding(8, 6, "DDTEK", 2714757);
		
			cgc_init_holding(8, 7, "PALM", 4294967295);
		
			cgc_init_holding(8, 8, "CROMU", 13154036);
		
			cgc_init_holding(8, 9, "PIRATE", 1984745);
		
			cgc_init_holding(8, 10, "MAPLE", 10440271);
		
			cgc_init_holding(9, 0, "GOOG", 2806291);
		
			cgc_init_holding(9, 1, "SK3WL", 2472935);
		
			cgc_init_holding(9, 2, "NRFIN", 10294218);
		
			cgc_init_holding(9, 3, "KPRCA", 1667285);
		
			cgc_init_holding(9, 4, "AAPL", 12327449);
		
			cgc_init_holding(9, 5, "OAK", 5585729);
		
			cgc_init_holding(9, 6, "DDTEK", 4294967295);
		
			cgc_init_holding(9, 7, "PALM", 7133955);
		
			cgc_init_holding(9, 8, "CROMU", 3133595);
		
			cgc_init_holding(9, 9, "PIRATE", 11437347);
		
			cgc_init_holding(9, 10, "MAPLE", 2946842);
		
			cgc_init_holding(10, 0, "GOOG", 15636185);
		
			cgc_init_holding(10, 1, "SK3WL", 3810043);
		
			cgc_init_holding(10, 2, "NRFIN", 1757482);
		
			cgc_init_holding(10, 3, "KPRCA", 7349362);
		
			cgc_init_holding(10, 4, "AAPL", 2772326);
		
			cgc_init_holding(10, 5, "OAK", 6657587);
		
			cgc_init_holding(10, 6, "DDTEK", 4557832);
		
			cgc_init_holding(10, 7, "PALM", 4294967295);
		
			cgc_init_holding(10, 8, "CROMU", 1007084);
		
			cgc_init_holding(10, 9, "PIRATE", 11768340);
		
			cgc_init_holding(10, 10, "MAPLE", 14135472);
		
			cgc_init_holding(11, 0, "GOOG", 8960182);
		
			cgc_init_holding(11, 1, "SK3WL", 4294967295);
		
			cgc_init_holding(11, 2, "NRFIN", 12269480);
		
			cgc_init_holding(11, 3, "KPRCA", 11421740);
		
			cgc_init_holding(11, 4, "AAPL", 9016835);
		
			cgc_init_holding(11, 5, "OAK", 11283725);
		
			cgc_init_holding(11, 6, "DDTEK", 3155420);
		
			cgc_init_holding(11, 7, "PALM", 14404065);
		
			cgc_init_holding(11, 8, "CROMU", 6893048);
		
			cgc_init_holding(11, 9, "PIRATE", 13478505);
		
			cgc_init_holding(11, 10, "MAPLE", 14703193);
		
			cgc_init_holding(12, 0, "GOOG", 11688733);
		
			cgc_init_holding(12, 1, "SK3WL", 13295258);
		
			cgc_init_holding(12, 2, "NRFIN", 15108918);
		
			cgc_init_holding(12, 3, "KPRCA", 14035081);
		
			cgc_init_holding(12, 4, "AAPL", 16044264);
		
			cgc_init_holding(12, 5, "OAK", 16391840);
		
			cgc_init_holding(12, 6, "DDTEK", 4294967295);
		
			cgc_init_holding(12, 7, "PALM", 12502629);
		
			cgc_init_holding(12, 8, "CROMU", 12604407);
		
			cgc_init_holding(12, 9, "PIRATE", 10121798);
		
			cgc_init_holding(12, 10, "MAPLE", 9433220);
		
			cgc_init_holding(13, 0, "GOOG", 11524495);
		
			cgc_init_holding(13, 1, "SK3WL", 1168846);
		
			cgc_init_holding(13, 2, "NRFIN", 3230299);
		
			cgc_init_holding(13, 3, "KPRCA", 2193972);
		
			cgc_init_holding(13, 4, "AAPL", 8841774);
		
			cgc_init_holding(13, 5, "OAK", 5088434);
		
			cgc_init_holding(13, 6, "DDTEK", 4294967295);
		
			cgc_init_holding(13, 7, "PALM", 11436443);
		
			cgc_init_holding(13, 8, "CROMU", 6832703);
		
			cgc_init_holding(13, 9, "PIRATE", 1615197);
		
			cgc_init_holding(13, 10, "MAPLE", 14707618);
		
			cgc_init_holding(14, 0, "GOOG", 11979219);
		
			cgc_init_holding(14, 1, "SK3WL", 4294967295);
		
			cgc_init_holding(14, 2, "NRFIN", 4503091);
		
			cgc_init_holding(14, 3, "KPRCA", 10393294);
		
			cgc_init_holding(14, 4, "AAPL", 13581203);
		
			cgc_init_holding(14, 5, "OAK", 15458811);
		
			cgc_init_holding(14, 6, "DDTEK", 1351048);
		
			cgc_init_holding(14, 7, "PALM", 11574131);
		
			cgc_init_holding(14, 8, "CROMU", 9216316);
		
			cgc_init_holding(14, 9, "PIRATE", 7530688);
		
			cgc_init_holding(14, 10, "MAPLE", 1355327);
		
			cgc_init_holding(15, 0, "GOOG", 3608426);
		
			cgc_init_holding(15, 1, "SK3WL", 4294967295);
		
			cgc_init_holding(15, 2, "NRFIN", 6898679);
		
			cgc_init_holding(15, 3, "KPRCA", 3984264);
		
			cgc_init_holding(15, 4, "AAPL", 5892330);
		
			cgc_init_holding(15, 5, "OAK", 16657794);
		
			cgc_init_holding(15, 6, "DDTEK", 3241989);
		
			cgc_init_holding(15, 7, "PALM", 1396362);
		
			cgc_init_holding(15, 8, "CROMU", 5049554);
		
			cgc_init_holding(15, 9, "PIRATE", 14805136);
		
			cgc_init_holding(15, 10, "MAPLE", 15810129);
		
			cgc_init_holding(16, 0, "GOOG", 10472799);
		
			cgc_init_holding(16, 1, "SK3WL", 11170086);
		
			cgc_init_holding(16, 2, "NRFIN", 13261757);
		
			cgc_init_holding(16, 3, "KPRCA", 4277534);
		
			cgc_init_holding(16, 4, "AAPL", 13749354);
		
			cgc_init_holding(16, 5, "OAK", 5570437);
		
			cgc_init_holding(16, 6, "DDTEK", 4294967295);
		
			cgc_init_holding(16, 7, "PALM", 10770226);
		
			cgc_init_holding(16, 8, "CROMU", 6944056);
		
			cgc_init_holding(16, 9, "PIRATE", 10885405);
		
			cgc_init_holding(16, 10, "MAPLE", 7438621);
		
			cgc_init_holding(17, 0, "GOOG", 1160878);
		
			cgc_init_holding(17, 1, "SK3WL", 10548236);
		
			cgc_init_holding(17, 2, "NRFIN", 1045249);
		
			cgc_init_holding(17, 3, "KPRCA", 1080544);
		
			cgc_init_holding(17, 4, "AAPL", 14443389);
		
			cgc_init_holding(17, 5, "OAK", 15469281);
		
			cgc_init_holding(17, 6, "DDTEK", 4294967295);
		
			cgc_init_holding(17, 7, "PALM", 5223098);
		
			cgc_init_holding(17, 8, "CROMU", 9362632);
		
			cgc_init_holding(17, 9, "PIRATE", 3557867);
		
			cgc_init_holding(17, 10, "MAPLE", 3424844);
		
			cgc_init_holding(18, 0, "GOOG", 10955106);
		
			cgc_init_holding(18, 1, "SK3WL", 6616950);
		
			cgc_init_holding(18, 2, "NRFIN", 12400890);
		
			cgc_init_holding(18, 3, "KPRCA", 7731846);
		
			cgc_init_holding(18, 4, "AAPL", 10431312);
		
			cgc_init_holding(18, 5, "OAK", 7502579);
		
			cgc_init_holding(18, 6, "DDTEK", 9146814);
		
			cgc_init_holding(18, 7, "PALM", 4294967295);
		
			cgc_init_holding(18, 8, "CROMU", 5557237);
		
			cgc_init_holding(18, 9, "PIRATE", 12472140);
		
			cgc_init_holding(18, 10, "MAPLE", 10605366);
		
			cgc_init_holding(19, 0, "GOOG", 11682743);
		
			cgc_init_holding(19, 1, "SK3WL", 12213053);
		
			cgc_init_holding(19, 2, "NRFIN", 13150087);
		
			cgc_init_holding(19, 3, "KPRCA", 1058239);
		
			cgc_init_holding(19, 4, "AAPL", 11739330);
		
			cgc_init_holding(19, 5, "OAK", 8524322);
		
			cgc_init_holding(19, 6, "DDTEK", 4294967295);
		
			cgc_init_holding(19, 7, "PALM", 6767717);
		
			cgc_init_holding(19, 8, "CROMU", 16382912);
		
			cgc_init_holding(19, 9, "PIRATE", 7020133);
		
			cgc_init_holding(19, 10, "MAPLE", 10949651);
		
			cgc_init_holding(20, 0, "GOOG", 6361454);
		
			cgc_init_holding(20, 1, "SK3WL", 10624090);
		
			cgc_init_holding(20, 2, "NRFIN", 9729863);
		
			cgc_init_holding(20, 3, "KPRCA", 5489966);
		
			cgc_init_holding(20, 4, "AAPL", 1644367);
		
			cgc_init_holding(20, 5, "OAK", 13704543);
		
			cgc_init_holding(20, 6, "DDTEK", 13296132);
		
			cgc_init_holding(20, 7, "PALM", 4294967295);
		
			cgc_init_holding(20, 8, "CROMU", 12534300);
		
			cgc_init_holding(20, 9, "PIRATE", 3314227);
		
			cgc_init_holding(20, 10, "MAPLE", 8091103);
		
			cgc_init_holding(21, 0, "GOOG", 15116102);
		
			cgc_init_holding(21, 1, "SK3WL", 4294967295);
		
			cgc_init_holding(21, 2, "NRFIN", 7163303);
		
			cgc_init_holding(21, 3, "KPRCA", 2411851);
		
			cgc_init_holding(21, 4, "AAPL", 1282178);
		
			cgc_init_holding(21, 5, "OAK", 3917628);
		
			cgc_init_holding(21, 6, "DDTEK", 10812358);
		
			cgc_init_holding(21, 7, "PALM", 15979282);
		
			cgc_init_holding(21, 8, "CROMU", 9688700);
		
			cgc_init_holding(21, 9, "PIRATE", 7870488);
		
			cgc_init_holding(21, 10, "MAPLE", 6164509);
		
			cgc_init_holding(22, 0, "GOOG", 4077423);
		
			cgc_init_holding(22, 1, "SK3WL", 4294967295);
		
			cgc_init_holding(22, 2, "NRFIN", 9445055);
		
			cgc_init_holding(22, 3, "KPRCA", 12406389);
		
			cgc_init_holding(22, 4, "AAPL", 13620598);
		
			cgc_init_holding(22, 5, "OAK", 3267007);
		
			cgc_init_holding(22, 6, "DDTEK", 4471790);
		
			cgc_init_holding(22, 7, "PALM", 13305435);
		
			cgc_init_holding(22, 8, "CROMU", 4483329);
		
			cgc_init_holding(22, 9, "PIRATE", 5539467);
		
			cgc_init_holding(22, 10, "MAPLE", 16179529);
		
			cgc_init_holding(23, 0, "GOOG", 15257167);
		
			cgc_init_holding(23, 1, "SK3WL", 4086382);
		
			cgc_init_holding(23, 2, "NRFIN", 10537523);
		
			cgc_init_holding(23, 3, "KPRCA", 1924550);
		
			cgc_init_holding(23, 4, "AAPL", 7884583);
		
			cgc_init_holding(23, 5, "OAK", 7048308);
		
			cgc_init_holding(23, 6, "DDTEK", 4294967295);
		
			cgc_init_holding(23, 7, "PALM", 6235064);
		
			cgc_init_holding(23, 8, "CROMU", 2426566);
		
			cgc_init_holding(23, 9, "PIRATE", 15526648);
		
			cgc_init_holding(23, 10, "MAPLE", 6321120);
		
			cgc_init_holding(24, 0, "GOOG", 1065341);
		
			cgc_init_holding(24, 1, "SK3WL", 11509928);
		
			cgc_init_holding(24, 2, "NRFIN", 2120379);
		
			cgc_init_holding(24, 3, "KPRCA", 8701824);
		
			cgc_init_holding(24, 4, "AAPL", 9024411);
		
			cgc_init_holding(24, 5, "OAK", 16086740);
		
			cgc_init_holding(24, 6, "DDTEK", 4294967295);
		
			cgc_init_holding(24, 7, "PALM", 11273924);
		
			cgc_init_holding(24, 8, "CROMU", 8791335);
		
			cgc_init_holding(24, 9, "PIRATE", 8773724);
		
			cgc_init_holding(24, 10, "MAPLE", 15272393);
		
			cgc_init_holding(25, 0, "GOOG", 4140026);
		
			cgc_init_holding(25, 1, "SK3WL", 1454170);
		
			cgc_init_holding(25, 2, "NRFIN", 5145732);
		
			cgc_init_holding(25, 3, "KPRCA", 9224234);
		
			cgc_init_holding(25, 4, "AAPL", 8689009);
		
			cgc_init_holding(25, 5, "OAK", 16382073);
		
			cgc_init_holding(25, 6, "DDTEK", 4294967295);
		
			cgc_init_holding(25, 7, "PALM", 6269156);
		
			cgc_init_holding(25, 8, "CROMU", 13240935);
		
			cgc_init_holding(25, 9, "PIRATE", 14765083);
		
			cgc_init_holding(25, 10, "MAPLE", 4798408);
		
			cgc_init_holding(26, 0, "GOOG", 2784024);
		
			cgc_init_holding(26, 1, "SK3WL", 13549293);
		
			cgc_init_holding(26, 2, "NRFIN", 2667817);
		
			cgc_init_holding(26, 3, "KPRCA", 3492991);
		
			cgc_init_holding(26, 4, "AAPL", 3847288);
		
			cgc_init_holding(26, 5, "OAK", 5313095);
		
			cgc_init_holding(26, 6, "DDTEK", 6009818);
		
			cgc_init_holding(26, 7, "PALM", 4294967295);
		
			cgc_init_holding(26, 8, "CROMU", 8466828);
		
			cgc_init_holding(26, 9, "PIRATE", 1507424);
		
			cgc_init_holding(26, 10, "MAPLE", 14210083);
		
			cgc_init_holding(27, 0, "GOOG", 8770132);
		
			cgc_init_holding(27, 1, "SK3WL", 4294967295);
		
			cgc_init_holding(27, 2, "NRFIN", 7530052);
		
			cgc_init_holding(27, 3, "KPRCA", 9274559);
		
			cgc_init_holding(27, 4, "AAPL", 16244414);
		
			cgc_init_holding(27, 5, "OAK", 13591144);
		
			cgc_init_holding(27, 6, "DDTEK", 12820445);
		
			cgc_init_holding(27, 7, "PALM", 7494192);
		
			cgc_init_holding(27, 8, "CROMU", 3214744);
		
			cgc_init_holding(27, 9, "PIRATE", 9732092);
		
			cgc_init_holding(27, 10, "MAPLE", 5384540);
		
			cgc_init_holding(28, 0, "GOOG", 14101661);
		
			cgc_init_holding(28, 1, "SK3WL", 9880693);
		
			cgc_init_holding(28, 2, "NRFIN", 4824828);
		
			cgc_init_holding(28, 3, "KPRCA", 6640789);
		
			cgc_init_holding(28, 4, "AAPL", 5985061);
		
			cgc_init_holding(28, 5, "OAK", 12082003);
		
			cgc_init_holding(28, 6, "DDTEK", 4294967295);
		
			cgc_init_holding(28, 7, "PALM", 11992980);
		
			cgc_init_holding(28, 8, "CROMU", 6663090);
		
			cgc_init_holding(28, 9, "PIRATE", 15536331);
		
			cgc_init_holding(28, 10, "MAPLE", 1693762);
		
			cgc_init_holding(29, 0, "GOOG", 2499199);
		
			cgc_init_holding(29, 1, "SK3WL", 4406436);
		
			cgc_init_holding(29, 2, "NRFIN", 14519628);
		
			cgc_init_holding(29, 3, "KPRCA", 7419909);
		
			cgc_init_holding(29, 4, "AAPL", 10165991);
		
			cgc_init_holding(29, 5, "OAK", 4372799);
		
			cgc_init_holding(29, 6, "DDTEK", 6544820);
		
			cgc_init_holding(29, 7, "PALM", 4294967295);
		
			cgc_init_holding(29, 8, "CROMU", 16537451);
		
			cgc_init_holding(29, 9, "PIRATE", 1716661);
		
			cgc_init_holding(29, 10, "MAPLE", 5788997);
		
			cgc_init_holding(30, 0, "GOOG", 6611019);
		
			cgc_init_holding(30, 1, "SK3WL", 12997587);
		
			cgc_init_holding(30, 2, "NRFIN", 1091133);
		
			cgc_init_holding(30, 3, "KPRCA", 15135738);
		
			cgc_init_holding(30, 4, "AAPL", 8348263);
		
			cgc_init_holding(30, 5, "OAK", 4912346);
		
			cgc_init_holding(30, 6, "DDTEK", 4385542);
		
			cgc_init_holding(30, 7, "PALM", 4294967295);
		
			cgc_init_holding(30, 8, "CROMU", 15877165);
		
			cgc_init_holding(30, 9, "PIRATE", 15099072);
		
			cgc_init_holding(30, 10, "MAPLE", 1874078);
		
			cgc_init_holding(31, 0, "GOOG", 16304977);
		
			cgc_init_holding(31, 1, "SK3WL", 4294967295);
		
			cgc_init_holding(31, 2, "NRFIN", 5052570);
		
			cgc_init_holding(31, 3, "KPRCA", 2877027);
		
			cgc_init_holding(31, 4, "AAPL", 4308592);
		
			cgc_init_holding(31, 5, "OAK", 1627498);
		
			cgc_init_holding(31, 6, "DDTEK", 3976235);
		
			cgc_init_holding(31, 7, "PALM", 9268624);
		
			cgc_init_holding(31, 8, "CROMU", 5030385);
		
			cgc_init_holding(31, 9, "PIRATE", 3795706);
		
			cgc_init_holding(31, 10, "MAPLE", 5022202);
		
			cgc_init_holding(32, 0, "GOOG", 16145286);
		
			cgc_init_holding(32, 1, "SK3WL", 15701401);
		
			cgc_init_holding(32, 2, "NRFIN", 7052302);
		
			cgc_init_holding(32, 3, "KPRCA", 8553136);
		
			cgc_init_holding(32, 4, "AAPL", 14804565);
		
			cgc_init_holding(32, 5, "OAK", 7324258);
		
			cgc_init_holding(32, 6, "DDTEK", 4294967295);
		
			cgc_init_holding(32, 7, "PALM", 10434500);
		
			cgc_init_holding(32, 8, "CROMU", 14462869);
		
			cgc_init_holding(32, 9, "PIRATE", 13583913);
		
			cgc_init_holding(32, 10, "MAPLE", 10595086);
		
			cgc_init_holding(33, 0, "GOOG", 13202499);
		
			cgc_init_holding(33, 1, "SK3WL", 4294967295);
		
			cgc_init_holding(33, 2, "NRFIN", 12766986);
		
			cgc_init_holding(33, 3, "KPRCA", 12046145);
		
			cgc_init_holding(33, 4, "AAPL", 11015974);
		
			cgc_init_holding(33, 5, "OAK", 16370510);
		
			cgc_init_holding(33, 6, "DDTEK", 3796352);
		
			cgc_init_holding(33, 7, "PALM", 13760909);
		
			cgc_init_holding(33, 8, "CROMU", 15326706);
		
			cgc_init_holding(33, 9, "PIRATE", 1693165);
		
			cgc_init_holding(33, 10, "MAPLE", 6146198);
		
			cgc_init_holding(34, 0, "GOOG", 14201410);
		
			cgc_init_holding(34, 1, "SK3WL", 8511288);
		
			cgc_init_holding(34, 2, "NRFIN", 1063994);
		
			cgc_init_holding(34, 3, "KPRCA", 6268552);
		
			cgc_init_holding(34, 4, "AAPL", 15198355);
		
			cgc_init_holding(34, 5, "OAK", 15873769);
		
			cgc_init_holding(34, 6, "DDTEK", 4294967295);
		
			cgc_init_holding(34, 7, "PALM", 6637311);
		
			cgc_init_holding(34, 8, "CROMU", 16288512);
		
			cgc_init_holding(34, 9, "PIRATE", 10642319);
		
			cgc_init_holding(34, 10, "MAPLE", 7302469);
		
			cgc_init_holding(35, 0, "GOOG", 16050794);
		
			cgc_init_holding(35, 1, "SK3WL", 4294967295);
		
			cgc_init_holding(35, 2, "NRFIN", 3856488);
		
			cgc_init_holding(35, 3, "KPRCA", 4569063);
		
			cgc_init_holding(35, 4, "AAPL", 15567455);
		
			cgc_init_holding(35, 5, "OAK", 2392423);
		
			cgc_init_holding(35, 6, "DDTEK", 16498540);
		
			cgc_init_holding(35, 7, "PALM", 5971020);
		
			cgc_init_holding(35, 8, "CROMU", 4331483);
		
			cgc_init_holding(35, 9, "PIRATE", 15865335);
		
			cgc_init_holding(35, 10, "MAPLE", 11754313);
		
			cgc_init_holding(36, 0, "GOOG", 2479175);
		
			cgc_init_holding(36, 1, "SK3WL", 4294967295);
		
			cgc_init_holding(36, 2, "NRFIN", 3822240);
		
			cgc_init_holding(36, 3, "KPRCA", 11635880);
		
			cgc_init_holding(36, 4, "AAPL", 8990382);
		
			cgc_init_holding(36, 5, "OAK", 1264252);
		
			cgc_init_holding(36, 6, "DDTEK", 2171273);
		
			cgc_init_holding(36, 7, "PALM", 9414321);
		
			cgc_init_holding(36, 8, "CROMU", 14730966);
		
			cgc_init_holding(36, 9, "PIRATE", 7244390);
		
			cgc_init_holding(36, 10, "MAPLE", 8947020);
		
			cgc_init_holding(37, 0, "GOOG", 15679785);
		
			cgc_init_holding(37, 1, "SK3WL", 8646879);
		
			cgc_init_holding(37, 2, "NRFIN", 8806663);
		
			cgc_init_holding(37, 3, "KPRCA", 5198906);
		
			cgc_init_holding(37, 4, "AAPL", 12170318);
		
			cgc_init_holding(37, 5, "OAK", 8386977);
		
			cgc_init_holding(37, 6, "DDTEK", 4294967295);
		
			cgc_init_holding(37, 7, "PALM", 11035897);
		
			cgc_init_holding(37, 8, "CROMU", 7972249);
		
			cgc_init_holding(37, 9, "PIRATE", 9495625);
		
			cgc_init_holding(37, 10, "MAPLE", 14516338);
		
			cgc_init_holding(38, 0, "GOOG", 15969557);
		
			cgc_init_holding(38, 1, "SK3WL", 13218669);
		
			cgc_init_holding(38, 2, "NRFIN", 6567289);
		
			cgc_init_holding(38, 3, "KPRCA", 13161176);
		
			cgc_init_holding(38, 4, "AAPL", 12798783);
		
			cgc_init_holding(38, 5, "OAK", 4921208);
		
			cgc_init_holding(38, 6, "DDTEK", 4294967295);
		
			cgc_init_holding(38, 7, "PALM", 6433043);
		
			cgc_init_holding(38, 8, "CROMU", 14405305);
		
			cgc_init_holding(38, 9, "PIRATE", 2158462);
		
			cgc_init_holding(38, 10, "MAPLE", 13782478);
		
			cgc_init_holding(39, 0, "GOOG", 4860109);
		
			cgc_init_holding(39, 1, "SK3WL", 4294967295);
		
			cgc_init_holding(39, 2, "NRFIN", 1571076);
		
			cgc_init_holding(39, 3, "KPRCA", 13933799);
		
			cgc_init_holding(39, 4, "AAPL", 7004055);
		
			cgc_init_holding(39, 5, "OAK", 12118951);
		
			cgc_init_holding(39, 6, "DDTEK", 11810231);
		
			cgc_init_holding(39, 7, "PALM", 14670828);
		
			cgc_init_holding(39, 8, "CROMU", 4298111);
		
			cgc_init_holding(39, 9, "PIRATE", 3730513);
		
			cgc_init_holding(39, 10, "MAPLE", 3767108);
		
			cgc_init_holding(40, 0, "GOOG", 4822938);
		
			cgc_init_holding(40, 1, "SK3WL", 5772139);
		
			cgc_init_holding(40, 2, "NRFIN", 7993294);
		
			cgc_init_holding(40, 3, "KPRCA", 8806511);
		
			cgc_init_holding(40, 4, "AAPL", 9141741);
		
			cgc_init_holding(40, 5, "OAK", 2945848);
		
			cgc_init_holding(40, 6, "DDTEK", 4294967295);
		
			cgc_init_holding(40, 7, "PALM", 16722448);
		
			cgc_init_holding(40, 8, "CROMU", 12282640);
		
			cgc_init_holding(40, 9, "PIRATE", 14585954);
		
			cgc_init_holding(40, 10, "MAPLE", 9488914);
		
			cgc_init_holding(41, 0, "GOOG", 16777118);
		
			cgc_init_holding(41, 1, "SK3WL", 2552391);
		
			cgc_init_holding(41, 2, "NRFIN", 10080659);
		
			cgc_init_holding(41, 3, "KPRCA", 8860583);
		
			cgc_init_holding(41, 4, "AAPL", 1356122);
		
			cgc_init_holding(41, 5, "OAK", 4099862);
		
			cgc_init_holding(41, 6, "DDTEK", 5354722);
		
			cgc_init_holding(41, 7, "PALM", 4294967295);
		
			cgc_init_holding(41, 8, "CROMU", 6737652);
		
			cgc_init_holding(41, 9, "PIRATE", 6075612);
		
			cgc_init_holding(41, 10, "MAPLE", 15594271);
		
			cgc_init_holding(42, 0, "GOOG", 13790057);
		
			cgc_init_holding(42, 1, "SK3WL", 5159107);
		
			cgc_init_holding(42, 2, "NRFIN", 5646950);
		
			cgc_init_holding(42, 3, "KPRCA", 1164374);
		
			cgc_init_holding(42, 4, "AAPL", 2481370);
		
			cgc_init_holding(42, 5, "OAK", 2834358);
		
			cgc_init_holding(42, 6, "DDTEK", 8643482);
		
			cgc_init_holding(42, 7, "PALM", 4294967295);
		
			cgc_init_holding(42, 8, "CROMU", 1215390);
		
			cgc_init_holding(42, 9, "PIRATE", 3940411);
		
			cgc_init_holding(42, 10, "MAPLE", 9107762);
		
			cgc_init_holding(43, 0, "GOOG", 7702169);
		
			cgc_init_holding(43, 1, "SK3WL", 4294967295);
		
			cgc_init_holding(43, 2, "NRFIN", 10362436);
		
			cgc_init_holding(43, 3, "KPRCA", 15077270);
		
			cgc_init_holding(43, 4, "AAPL", 14129608);
		
			cgc_init_holding(43, 5, "OAK", 14233452);
		
			cgc_init_holding(43, 6, "DDTEK", 16448692);
		
			cgc_init_holding(43, 7, "PALM", 9150686);
		
			cgc_init_holding(43, 8, "CROMU", 10499415);
		
			cgc_init_holding(43, 9, "PIRATE", 2691104);
		
			cgc_init_holding(43, 10, "MAPLE", 15821369);
		
			cgc_init_holding(44, 0, "GOOG", 9713656);
		
			cgc_init_holding(44, 1, "SK3WL", 4753509);
		
			cgc_init_holding(44, 2, "NRFIN", 14443410);
		
			cgc_init_holding(44, 3, "KPRCA", 7617582);
		
			cgc_init_holding(44, 4, "AAPL", 8641563);
		
			cgc_init_holding(44, 5, "OAK", 11563330);
		
			cgc_init_holding(44, 6, "DDTEK", 13496268);
		
			cgc_init_holding(44, 7, "PALM", 4294967295);
		
			cgc_init_holding(44, 8, "CROMU", 16040095);
		
			cgc_init_holding(44, 9, "PIRATE", 5411080);
		
			cgc_init_holding(44, 10, "MAPLE", 9992150);
		
			cgc_init_holding(45, 0, "GOOG", 9704535);
		
			cgc_init_holding(45, 1, "SK3WL", 14950974);
		
			cgc_init_holding(45, 2, "NRFIN", 3479247);
		
			cgc_init_holding(45, 3, "KPRCA", 8800218);
		
			cgc_init_holding(45, 4, "AAPL", 10062457);
		
			cgc_init_holding(45, 5, "OAK", 12240112);
		
			cgc_init_holding(45, 6, "DDTEK", 4294967295);
		
			cgc_init_holding(45, 7, "PALM", 5254871);
		
			cgc_init_holding(45, 8, "CROMU", 12010930);
		
			cgc_init_holding(45, 9, "PIRATE", 5428519);
		
			cgc_init_holding(45, 10, "MAPLE", 3168296);
		
			cgc_init_holding(46, 0, "GOOG", 15197400);
		
			cgc_init_holding(46, 1, "SK3WL", 4294967295);
		
			cgc_init_holding(46, 2, "NRFIN", 12293353);
		
			cgc_init_holding(46, 3, "KPRCA", 7231493);
		
			cgc_init_holding(46, 4, "AAPL", 15038197);
		
			cgc_init_holding(46, 5, "OAK", 7537714);
		
			cgc_init_holding(46, 6, "DDTEK", 8976901);
		
			cgc_init_holding(46, 7, "PALM", 5854179);
		
			cgc_init_holding(46, 8, "CROMU", 13599544);
		
			cgc_init_holding(46, 9, "PIRATE", 6037412);
		
			cgc_init_holding(46, 10, "MAPLE", 1147968);
		
			cgc_init_holding(47, 0, "GOOG", 14545414);
		
			cgc_init_holding(47, 1, "SK3WL", 4294967295);
		
			cgc_init_holding(47, 2, "NRFIN", 12402620);
		
			cgc_init_holding(47, 3, "KPRCA", 4575737);
		
			cgc_init_holding(47, 4, "AAPL", 7790090);
		
			cgc_init_holding(47, 5, "OAK", 3512099);
		
			cgc_init_holding(47, 6, "DDTEK", 7019948);
		
			cgc_init_holding(47, 7, "PALM", 4138803);
		
			cgc_init_holding(47, 8, "CROMU", 6069633);
		
			cgc_init_holding(47, 9, "PIRATE", 11084242);
		
			cgc_init_holding(47, 10, "MAPLE", 11015884);
		
			cgc_init_holding(48, 0, "GOOG", 4126452);
		
			cgc_init_holding(48, 1, "SK3WL", 4294967295);
		
			cgc_init_holding(48, 2, "NRFIN", 11633903);
		
			cgc_init_holding(48, 3, "KPRCA", 12098836);
		
			cgc_init_holding(48, 4, "AAPL", 13406575);
		
			cgc_init_holding(48, 5, "OAK", 5137850);
		
			cgc_init_holding(48, 6, "DDTEK", 13244385);
		
			cgc_init_holding(48, 7, "PALM", 16412901);
		
			cgc_init_holding(48, 8, "CROMU", 6759125);
		
			cgc_init_holding(48, 9, "PIRATE", 4359236);
		
			cgc_init_holding(48, 10, "MAPLE", 6563685);
		
			cgc_init_holding(49, 0, "GOOG", 7100466);
		
			cgc_init_holding(49, 1, "SK3WL", 13433096);
		
			cgc_init_holding(49, 2, "NRFIN", 10989497);
		
			cgc_init_holding(49, 3, "KPRCA", 2311380);
		
			cgc_init_holding(49, 4, "AAPL", 7502571);
		
			cgc_init_holding(49, 5, "OAK", 12389247);
		
			cgc_init_holding(49, 6, "DDTEK", 4294967295);
		
			cgc_init_holding(49, 7, "PALM", 3104833);
		
			cgc_init_holding(49, 8, "CROMU", 1310083);
		
			cgc_init_holding(49, 9, "PIRATE", 1396315);
		
			cgc_init_holding(49, 10, "MAPLE", 16022222);
		
			cgc_init_holding(50, 0, "GOOG", 9521571);
		
			cgc_init_holding(50, 1, "SK3WL", 9851935);
		
			cgc_init_holding(50, 2, "NRFIN", 6779201);
		
			cgc_init_holding(50, 3, "KPRCA", 8971014);
		
			cgc_init_holding(50, 4, "AAPL", 10194938);
		
			cgc_init_holding(50, 5, "OAK", 9568752);
		
			cgc_init_holding(50, 6, "DDTEK", 4294967295);
		
			cgc_init_holding(50, 7, "PALM", 12504729);
		
			cgc_init_holding(50, 8, "CROMU", 16567495);
		
			cgc_init_holding(50, 9, "PIRATE", 12482248);
		
			cgc_init_holding(50, 10, "MAPLE", 14402093);
		
			cgc_init_holding(51, 0, "GOOG", 8938918);
		
			cgc_init_holding(51, 1, "SK3WL", 16422979);
		
			cgc_init_holding(51, 2, "NRFIN", 9717293);
		
			cgc_init_holding(51, 3, "KPRCA", 12927708);
		
			cgc_init_holding(51, 4, "AAPL", 4023909);
		
			cgc_init_holding(51, 5, "OAK", 4624917);
		
			cgc_init_holding(51, 6, "DDTEK", 4294967295);
		
			cgc_init_holding(51, 7, "PALM", 11195165);
		
			cgc_init_holding(51, 8, "CROMU", 3630205);
		
			cgc_init_holding(51, 9, "PIRATE", 1666946);
		
			cgc_init_holding(51, 10, "MAPLE", 4870922);
		
			cgc_init_holding(52, 0, "GOOG", 1282578);
		
			cgc_init_holding(52, 1, "SK3WL", 3522009);
		
			cgc_init_holding(52, 2, "NRFIN", 14292547);
		
			cgc_init_holding(52, 3, "KPRCA", 1776975);
		
			cgc_init_holding(52, 4, "AAPL", 6899032);
		
			cgc_init_holding(52, 5, "OAK", 11253110);
		
			cgc_init_holding(52, 6, "DDTEK", 13974089);
		
			cgc_init_holding(52, 7, "PALM", 4294967295);
		
			cgc_init_holding(52, 8, "CROMU", 9976917);
		
			cgc_init_holding(52, 9, "PIRATE", 4318376);
		
			cgc_init_holding(52, 10, "MAPLE", 11286875);
		
			cgc_init_holding(53, 0, "GOOG", 12585617);
		
			cgc_init_holding(53, 1, "SK3WL", 7232735);
		
			cgc_init_holding(53, 2, "NRFIN", 1775133);
		
			cgc_init_holding(53, 3, "KPRCA", 15060652);
		
			cgc_init_holding(53, 4, "AAPL", 14787293);
		
			cgc_init_holding(53, 5, "OAK", 5493411);
		
			cgc_init_holding(53, 6, "DDTEK", 1941501);
		
			cgc_init_holding(53, 7, "PALM", 4294967295);
		
			cgc_init_holding(53, 8, "CROMU", 14717141);
		
			cgc_init_holding(53, 9, "PIRATE", 11124581);
		
			cgc_init_holding(53, 10, "MAPLE", 10364605);
		
			cgc_init_holding(54, 0, "GOOG", 13862266);
		
			cgc_init_holding(54, 1, "SK3WL", 4294967295);
		
			cgc_init_holding(54, 2, "NRFIN", 13113962);
		
			cgc_init_holding(54, 3, "KPRCA", 16235160);
		
			cgc_init_holding(54, 4, "AAPL", 10907064);
		
			cgc_init_holding(54, 5, "OAK", 5753074);
		
			cgc_init_holding(54, 6, "DDTEK", 3400066);
		
			cgc_init_holding(54, 7, "PALM", 8520428);
		
			cgc_init_holding(54, 8, "CROMU", 13315584);
		
			cgc_init_holding(54, 9, "PIRATE", 1092891);
		
			cgc_init_holding(54, 10, "MAPLE", 11637532);
		
			cgc_init_holding(55, 0, "GOOG", 8247773);
		
			cgc_init_holding(55, 1, "SK3WL", 4520806);
		
			cgc_init_holding(55, 2, "NRFIN", 12714003);
		
			cgc_init_holding(55, 3, "KPRCA", 12930141);
		
			cgc_init_holding(55, 4, "AAPL", 16665840);
		
			cgc_init_holding(55, 5, "OAK", 5912732);
		
			cgc_init_holding(55, 6, "DDTEK", 4294967295);
		
			cgc_init_holding(55, 7, "PALM", 3599110);
		
			cgc_init_holding(55, 8, "CROMU", 9691210);
		
			cgc_init_holding(55, 9, "PIRATE", 5729274);
		
			cgc_init_holding(55, 10, "MAPLE", 9155966);
		
			cgc_init_holding(56, 0, "GOOG", 2473636);
		
			cgc_init_holding(56, 1, "SK3WL", 8030245);
		
			cgc_init_holding(56, 2, "NRFIN", 2154361);
		
			cgc_init_holding(56, 3, "KPRCA", 15066579);
		
			cgc_init_holding(56, 4, "AAPL", 11435178);
		
			cgc_init_holding(56, 5, "OAK", 9445123);
		
			cgc_init_holding(56, 6, "DDTEK", 4294967295);
		
			cgc_init_holding(56, 7, "PALM", 15336216);
		
			cgc_init_holding(56, 8, "CROMU", 2024765);
		
			cgc_init_holding(56, 9, "PIRATE", 8916118);
		
			cgc_init_holding(56, 10, "MAPLE", 14447678);
		
			cgc_init_holding(57, 0, "GOOG", 9638472);
		
			cgc_init_holding(57, 1, "SK3WL", 8460099);
		
			cgc_init_holding(57, 2, "NRFIN", 16471372);
		
			cgc_init_holding(57, 3, "KPRCA", 5887745);
		
			cgc_init_holding(57, 4, "AAPL", 6038510);
		
			cgc_init_holding(57, 5, "OAK", 4216517);
		
			cgc_init_holding(57, 6, "DDTEK", 4294967295);
		
			cgc_init_holding(57, 7, "PALM", 15256299);
		
			cgc_init_holding(57, 8, "CROMU", 13022481);
		
			cgc_init_holding(57, 9, "PIRATE", 15319177);
		
			cgc_init_holding(57, 10, "MAPLE", 13204310);
		
			cgc_init_holding(58, 0, "GOOG", 13859747);
		
			cgc_init_holding(58, 1, "SK3WL", 4294967295);
		
			cgc_init_holding(58, 2, "NRFIN", 4166866);
		
			cgc_init_holding(58, 3, "KPRCA", 6713079);
		
			cgc_init_holding(58, 4, "AAPL", 7908228);
		
			cgc_init_holding(58, 5, "OAK", 15410039);
		
			cgc_init_holding(58, 6, "DDTEK", 16148226);
		
			cgc_init_holding(58, 7, "PALM", 1492497);
		
			cgc_init_holding(58, 8, "CROMU", 5704136);
		
			cgc_init_holding(58, 9, "PIRATE", 4759536);
		
			cgc_init_holding(58, 10, "MAPLE", 14976006);
		
			cgc_init_holding(59, 0, "GOOG", 6094082);
		
			cgc_init_holding(59, 1, "SK3WL", 2480789);
		
			cgc_init_holding(59, 2, "NRFIN", 16055547);
		
			cgc_init_holding(59, 3, "KPRCA", 7692201);
		
			cgc_init_holding(59, 4, "AAPL", 7394235);
		
			cgc_init_holding(59, 5, "OAK", 12207680);
		
			cgc_init_holding(59, 6, "DDTEK", 4294967295);
		
			cgc_init_holding(59, 7, "PALM", 15624481);
		
			cgc_init_holding(59, 8, "CROMU", 8729836);
		
			cgc_init_holding(59, 9, "PIRATE", 7247667);
		
			cgc_init_holding(59, 10, "MAPLE", 1864472);
		
			cgc_init_holding(60, 0, "GOOG", 6143374);
		
			cgc_init_holding(60, 1, "SK3WL", 6514718);
		
			cgc_init_holding(60, 2, "NRFIN", 8077271);
		
			cgc_init_holding(60, 3, "KPRCA", 10153214);
		
			cgc_init_holding(60, 4, "AAPL", 1822598);
		
			cgc_init_holding(60, 5, "OAK", 10901156);
		
			cgc_init_holding(60, 6, "DDTEK", 9443404);
		
			cgc_init_holding(60, 7, "PALM", 4294967295);
		
			cgc_init_holding(60, 8, "CROMU", 9853321);
		
			cgc_init_holding(60, 9, "PIRATE", 12226631);
		
			cgc_init_holding(60, 10, "MAPLE", 12759456);
		
			cgc_init_holding(61, 0, "GOOG", 15053460);
		
			cgc_init_holding(61, 1, "SK3WL", 2844003);
		
			cgc_init_holding(61, 2, "NRFIN", 13464004);
		
			cgc_init_holding(61, 3, "KPRCA", 9305531);
		
			cgc_init_holding(61, 4, "AAPL", 10214556);
		
			cgc_init_holding(61, 5, "OAK", 6983249);
		
			cgc_init_holding(61, 6, "DDTEK", 4294967295);
		
			cgc_init_holding(61, 7, "PALM", 1987918);
		
			cgc_init_holding(61, 8, "CROMU", 11312556);
		
			cgc_init_holding(61, 9, "PIRATE", 8102804);
		
			cgc_init_holding(61, 10, "MAPLE", 16147711);
		
			cgc_init_holding(62, 0, "GOOG", 2843061);
		
			cgc_init_holding(62, 1, "SK3WL", 4294967295);
		
			cgc_init_holding(62, 2, "NRFIN", 5779362);
		
			cgc_init_holding(62, 3, "KPRCA", 14292545);
		
			cgc_init_holding(62, 4, "AAPL", 15510736);
		
			cgc_init_holding(62, 5, "OAK", 2856217);
		
			cgc_init_holding(62, 6, "DDTEK", 11561860);
		
			cgc_init_holding(62, 7, "PALM", 16580772);
		
			cgc_init_holding(62, 8, "CROMU", 11043724);
		
			cgc_init_holding(62, 9, "PIRATE", 14155851);
		
			cgc_init_holding(62, 10, "MAPLE", 11034770);
		
			cgc_init_holding(63, 0, "GOOG", 14609439);
		
			cgc_init_holding(63, 1, "SK3WL", 10511271);
		
			cgc_init_holding(63, 2, "NRFIN", 1852432);
		
			cgc_init_holding(63, 3, "KPRCA", 10827303);
		
			cgc_init_holding(63, 4, "AAPL", 5241151);
		
			cgc_init_holding(63, 5, "OAK", 2778639);
		
			cgc_init_holding(63, 6, "DDTEK", 4294967295);
		
			cgc_init_holding(63, 7, "PALM", 13442907);
		
			cgc_init_holding(63, 8, "CROMU", 8417882);
		
			cgc_init_holding(63, 9, "PIRATE", 11015539);
		
			cgc_init_holding(63, 10, "MAPLE", 2447684);
		
			cgc_init_holding(64, 0, "GOOG", 6339394);
		
			cgc_init_holding(64, 1, "SK3WL", 3673932);
		
			cgc_init_holding(64, 2, "NRFIN", 2319024);
		
			cgc_init_holding(64, 3, "KPRCA", 1867974);
		
			cgc_init_holding(64, 4, "AAPL", 2271985);
		
			cgc_init_holding(64, 5, "OAK", 3711519);
		
			cgc_init_holding(64, 6, "DDTEK", 1942460);
		
			cgc_init_holding(64, 7, "PALM", 4294967295);
		
			cgc_init_holding(64, 8, "CROMU", 7933304);
		
			cgc_init_holding(64, 9, "PIRATE", 8379052);
		
			cgc_init_holding(64, 10, "MAPLE", 9294378);
		
			cgc_init_holding(65, 0, "GOOG", 2591017);
		
			cgc_init_holding(65, 1, "SK3WL", 5478390);
		
			cgc_init_holding(65, 2, "NRFIN", 3848650);
		
			cgc_init_holding(65, 3, "KPRCA", 9231715);
		
			cgc_init_holding(65, 4, "AAPL", 9178149);
		
			cgc_init_holding(65, 5, "OAK", 1417773);
		
			cgc_init_holding(65, 6, "DDTEK", 4294967295);
		
			cgc_init_holding(65, 7, "PALM", 3150120);
		
			cgc_init_holding(65, 8, "CROMU", 3591382);
		
			cgc_init_holding(65, 9, "PIRATE", 12120170);
		
			cgc_init_holding(65, 10, "MAPLE", 8404641);
		
			cgc_init_holding(66, 0, "GOOG", 3249878);
		
			cgc_init_holding(66, 1, "SK3WL", 5677542);
		
			cgc_init_holding(66, 2, "NRFIN", 2899829);
		
			cgc_init_holding(66, 3, "KPRCA", 4525060);
		
			cgc_init_holding(66, 4, "AAPL", 5684300);
		
			cgc_init_holding(66, 5, "OAK", 8285880);
		
			cgc_init_holding(66, 6, "DDTEK", 3114578);
		
			cgc_init_holding(66, 7, "PALM", 4294967295);
		
			cgc_init_holding(66, 8, "CROMU", 3136496);
		
			cgc_init_holding(66, 9, "PIRATE", 7436642);
		
			cgc_init_holding(66, 10, "MAPLE", 9557924);
		
			cgc_init_holding(67, 0, "GOOG", 9943232);
		
			cgc_init_holding(67, 1, "SK3WL", 10243760);
		
			cgc_init_holding(67, 2, "NRFIN", 11205024);
		
			cgc_init_holding(67, 3, "KPRCA", 5172102);
		
			cgc_init_holding(67, 4, "AAPL", 4061144);
		
			cgc_init_holding(67, 5, "OAK", 12408111);
		
			cgc_init_holding(67, 6, "DDTEK", 4294967295);
		
			cgc_init_holding(67, 7, "PALM", 14784684);
		
			cgc_init_holding(67, 8, "CROMU", 16070561);
		
			cgc_init_holding(67, 9, "PIRATE", 4604413);
		
			cgc_init_holding(67, 10, "MAPLE", 9280211);
		
			cgc_init_holding(68, 0, "GOOG", 10721570);
		
			cgc_init_holding(68, 1, "SK3WL", 4294967295);
		
			cgc_init_holding(68, 2, "NRFIN", 1371650);
		
			cgc_init_holding(68, 3, "KPRCA", 11461531);
		
			cgc_init_holding(68, 4, "AAPL", 3230262);
		
			cgc_init_holding(68, 5, "OAK", 2427359);
		
			cgc_init_holding(68, 6, "DDTEK", 1282727);
		
			cgc_init_holding(68, 7, "PALM", 7075011);
		
			cgc_init_holding(68, 8, "CROMU", 2277629);
		
			cgc_init_holding(68, 9, "PIRATE", 10275192);
		
			cgc_init_holding(68, 10, "MAPLE", 4250081);
		
			cgc_init_holding(69, 0, "GOOG", 11367300);
		
			cgc_init_holding(69, 1, "SK3WL", 4294967295);
		
			cgc_init_holding(69, 2, "NRFIN", 9873926);
		
			cgc_init_holding(69, 3, "KPRCA", 10169213);
		
			cgc_init_holding(69, 4, "AAPL", 4339652);
		
			cgc_init_holding(69, 5, "OAK", 8465192);
		
			cgc_init_holding(69, 6, "DDTEK", 1696409);
		
			cgc_init_holding(69, 7, "PALM", 6159680);
		
			cgc_init_holding(69, 8, "CROMU", 4010481);
		
			cgc_init_holding(69, 9, "PIRATE", 14469126);
		
			cgc_init_holding(69, 10, "MAPLE", 15804958);
		
			cgc_init_holding(70, 0, "GOOG", 6949049);
		
			cgc_init_holding(70, 1, "SK3WL", 4294967295);
		
			cgc_init_holding(70, 2, "NRFIN", 2358002);
		
			cgc_init_holding(70, 3, "KPRCA", 11345952);
		
			cgc_init_holding(70, 4, "AAPL", 12242159);
		
			cgc_init_holding(70, 5, "OAK", 2239732);
		
			cgc_init_holding(70, 6, "DDTEK", 5356987);
		
			cgc_init_holding(70, 7, "PALM", 11822903);
		
			cgc_init_holding(70, 8, "CROMU", 1714463);
		
			cgc_init_holding(70, 9, "PIRATE", 2558635);
		
			cgc_init_holding(70, 10, "MAPLE", 8127364);
		
			cgc_init_holding(71, 0, "GOOG", 13736182);
		
			cgc_init_holding(71, 1, "SK3WL", 16294150);
		
			cgc_init_holding(71, 2, "NRFIN", 4851774);
		
			cgc_init_holding(71, 3, "KPRCA", 2328528);
		
			cgc_init_holding(71, 4, "AAPL", 8097256);
		
			cgc_init_holding(71, 5, "OAK", 12756603);
		
			cgc_init_holding(71, 6, "DDTEK", 4294967295);
		
			cgc_init_holding(71, 7, "PALM", 10697697);
		
			cgc_init_holding(71, 8, "CROMU", 15419543);
		
			cgc_init_holding(71, 9, "PIRATE", 4160055);
		
			cgc_init_holding(71, 10, "MAPLE", 8095420);
		
			cgc_init_holding(72, 0, "GOOG", 4351306);
		
			cgc_init_holding(72, 1, "SK3WL", 4294967295);
		
			cgc_init_holding(72, 2, "NRFIN", 1464943);
		
			cgc_init_holding(72, 3, "KPRCA", 1728588);
		
			cgc_init_holding(72, 4, "AAPL", 13875405);
		
			cgc_init_holding(72, 5, "OAK", 11729595);
		
			cgc_init_holding(72, 6, "DDTEK", 12116345);
		
			cgc_init_holding(72, 7, "PALM", 9579724);
		
			cgc_init_holding(72, 8, "CROMU", 5214966);
		
			cgc_init_holding(72, 9, "PIRATE", 12151145);
		
			cgc_init_holding(72, 10, "MAPLE", 8362213);
		
			cgc_init_holding(73, 0, "GOOG", 10997557);
		
			cgc_init_holding(73, 1, "SK3WL", 4294967295);
		
			cgc_init_holding(73, 2, "NRFIN", 3512052);
		
			cgc_init_holding(73, 3, "KPRCA", 7866577);
		
			cgc_init_holding(73, 4, "AAPL", 8637268);
		
			cgc_init_holding(73, 5, "OAK", 2921250);
		
			cgc_init_holding(73, 6, "DDTEK", 15339788);
		
			cgc_init_holding(73, 7, "PALM", 6429327);
		
			cgc_init_holding(73, 8, "CROMU", 5708918);
		
			cgc_init_holding(73, 9, "PIRATE", 13740800);
		
			cgc_init_holding(73, 10, "MAPLE", 7077120);
		
			cgc_init_holding(74, 0, "GOOG", 16146022);
		
			cgc_init_holding(74, 1, "SK3WL", 4294967295);
		
			cgc_init_holding(74, 2, "NRFIN", 8084313);
		
			cgc_init_holding(74, 3, "KPRCA", 10747493);
		
			cgc_init_holding(74, 4, "AAPL", 9331574);
		
			cgc_init_holding(74, 5, "OAK", 14612865);
		
			cgc_init_holding(74, 6, "DDTEK", 14456201);
		
			cgc_init_holding(74, 7, "PALM", 15638824);
		
			cgc_init_holding(74, 8, "CROMU", 5114190);
		
			cgc_init_holding(74, 9, "PIRATE", 15954376);
		
			cgc_init_holding(74, 10, "MAPLE", 5308003);
		
			cgc_init_holding(75, 0, "GOOG", 7113924);
		
			cgc_init_holding(75, 1, "SK3WL", 4202627);
		
			cgc_init_holding(75, 2, "NRFIN", 7302506);
		
			cgc_init_holding(75, 3, "KPRCA", 14673068);
		
			cgc_init_holding(75, 4, "AAPL", 15710354);
		
			cgc_init_holding(75, 5, "OAK", 7975668);
		
			cgc_init_holding(75, 6, "DDTEK", 15730691);
		
			cgc_init_holding(75, 7, "PALM", 4294967295);
		
			cgc_init_holding(75, 8, "CROMU", 3410437);
		
			cgc_init_holding(75, 9, "PIRATE", 8906117);
		
			cgc_init_holding(75, 10, "MAPLE", 9414731);
		
			cgc_init_holding(76, 0, "GOOG", 14833268);
		
			cgc_init_holding(76, 1, "SK3WL", 5009385);
		
			cgc_init_holding(76, 2, "NRFIN", 16662223);
		
			cgc_init_holding(76, 3, "KPRCA", 12544022);
		
			cgc_init_holding(76, 4, "AAPL", 1708631);
		
			cgc_init_holding(76, 5, "OAK", 6890600);
		
			cgc_init_holding(76, 6, "DDTEK", 6346253);
		
			cgc_init_holding(76, 7, "PALM", 4294967295);
		
			cgc_init_holding(76, 8, "CROMU", 2017784);
		
			cgc_init_holding(76, 9, "PIRATE", 2516169);
		
			cgc_init_holding(76, 10, "MAPLE", 15957197);
		
			cgc_init_holding(77, 0, "GOOG", 16725064);
		
			cgc_init_holding(77, 1, "SK3WL", 4292927);
		
			cgc_init_holding(77, 2, "NRFIN", 11590977);
		
			cgc_init_holding(77, 3, "KPRCA", 15983349);
		
			cgc_init_holding(77, 4, "AAPL", 12612147);
		
			cgc_init_holding(77, 5, "OAK", 16268769);
		
			cgc_init_holding(77, 6, "DDTEK", 12190990);
		
			cgc_init_holding(77, 7, "PALM", 4294967295);
		
			cgc_init_holding(77, 8, "CROMU", 16133556);
		
			cgc_init_holding(77, 9, "PIRATE", 2124874);
		
			cgc_init_holding(77, 10, "MAPLE", 14701799);
		
			cgc_init_holding(78, 0, "GOOG", 2787457);
		
			cgc_init_holding(78, 1, "SK3WL", 5750399);
		
			cgc_init_holding(78, 2, "NRFIN", 16412843);
		
			cgc_init_holding(78, 3, "KPRCA", 15409168);
		
			cgc_init_holding(78, 4, "AAPL", 6932703);
		
			cgc_init_holding(78, 5, "OAK", 8020924);
		
			cgc_init_holding(78, 6, "DDTEK", 2190798);
		
			cgc_init_holding(78, 7, "PALM", 4294967295);
		
			cgc_init_holding(78, 8, "CROMU", 10638180);
		
			cgc_init_holding(78, 9, "PIRATE", 8047783);
		
			cgc_init_holding(78, 10, "MAPLE", 14872850);
		
			cgc_init_holding(79, 0, "GOOG", 5712747);
		
			cgc_init_holding(79, 1, "SK3WL", 4294967295);
		
			cgc_init_holding(79, 2, "NRFIN", 5038932);
		
			cgc_init_holding(79, 3, "KPRCA", 16287904);
		
			cgc_init_holding(79, 4, "AAPL", 7591532);
		
			cgc_init_holding(79, 5, "OAK", 1801423);
		
			cgc_init_holding(79, 6, "DDTEK", 4942595);
		
			cgc_init_holding(79, 7, "PALM", 6893675);
		
			cgc_init_holding(79, 8, "CROMU", 10679577);
		
			cgc_init_holding(79, 9, "PIRATE", 8771892);
		
			cgc_init_holding(79, 10, "MAPLE", 8812499);
		
			cgc_init_holding(80, 0, "GOOG", 3494735);
		
			cgc_init_holding(80, 1, "SK3WL", 4294967295);
		
			cgc_init_holding(80, 2, "NRFIN", 15660796);
		
			cgc_init_holding(80, 3, "KPRCA", 7079911);
		
			cgc_init_holding(80, 4, "AAPL", 3192245);
		
			cgc_init_holding(80, 5, "OAK", 8257291);
		
			cgc_init_holding(80, 6, "DDTEK", 1102113);
		
			cgc_init_holding(80, 7, "PALM", 9285787);
		
			cgc_init_holding(80, 8, "CROMU", 7689556);
		
			cgc_init_holding(80, 9, "PIRATE", 11300844);
		
			cgc_init_holding(80, 10, "MAPLE", 3570038);
		
			cgc_init_holding(81, 0, "GOOG", 3671913);
		
			cgc_init_holding(81, 1, "SK3WL", 14140569);
		
			cgc_init_holding(81, 2, "NRFIN", 1582316);
		
			cgc_init_holding(81, 3, "KPRCA", 8350548);
		
			cgc_init_holding(81, 4, "AAPL", 15291318);
		
			cgc_init_holding(81, 5, "OAK", 7800388);
		
			cgc_init_holding(81, 6, "DDTEK", 7152120);
		
			cgc_init_holding(81, 7, "PALM", 4294967295);
		
			cgc_init_holding(81, 8, "CROMU", 5563149);
		
			cgc_init_holding(81, 9, "PIRATE", 4914026);
		
			cgc_init_holding(81, 10, "MAPLE", 1023698);
		
			cgc_init_holding(82, 0, "GOOG", 16486627);
		
			cgc_init_holding(82, 1, "SK3WL", 6574802);
		
			cgc_init_holding(82, 2, "NRFIN", 16413030);
		
			cgc_init_holding(82, 3, "KPRCA", 14936637);
		
			cgc_init_holding(82, 4, "AAPL", 3672900);
		
			cgc_init_holding(82, 5, "OAK", 13902760);
		
			cgc_init_holding(82, 6, "DDTEK", 8258594);
		
			cgc_init_holding(82, 7, "PALM", 4294967295);
		
			cgc_init_holding(82, 8, "CROMU", 12641224);
		
			cgc_init_holding(82, 9, "PIRATE", 8376158);
		
			cgc_init_holding(82, 10, "MAPLE", 3275268);
		
			cgc_init_holding(83, 0, "GOOG", 11912262);
		
			cgc_init_holding(83, 1, "SK3WL", 6228655);
		
			cgc_init_holding(83, 2, "NRFIN", 14793059);
		
			cgc_init_holding(83, 3, "KPRCA", 7595741);
		
			cgc_init_holding(83, 4, "AAPL", 1758682);
		
			cgc_init_holding(83, 5, "OAK", 2460156);
		
			cgc_init_holding(83, 6, "DDTEK", 4294967295);
		
			cgc_init_holding(83, 7, "PALM", 10657454);
		
			cgc_init_holding(83, 8, "CROMU", 15520122);
		
			cgc_init_holding(83, 9, "PIRATE", 1399931);
		
			cgc_init_holding(83, 10, "MAPLE", 7799706);
		
			cgc_init_holding(84, 0, "GOOG", 14374714);
		
			cgc_init_holding(84, 1, "SK3WL", 4294967295);
		
			cgc_init_holding(84, 2, "NRFIN", 6560926);
		
			cgc_init_holding(84, 3, "KPRCA", 15669180);
		
			cgc_init_holding(84, 4, "AAPL", 12366596);
		
			cgc_init_holding(84, 5, "OAK", 9024028);
		
			cgc_init_holding(84, 6, "DDTEK", 7452913);
		
			cgc_init_holding(84, 7, "PALM", 10582196);
		
			cgc_init_holding(84, 8, "CROMU", 2746395);
		
			cgc_init_holding(84, 9, "PIRATE", 11199896);
		
			cgc_init_holding(84, 10, "MAPLE", 8404624);
		
			cgc_init_holding(85, 0, "GOOG", 10457180);
		
			cgc_init_holding(85, 1, "SK3WL", 8013075);
		
			cgc_init_holding(85, 2, "NRFIN", 8314568);
		
			cgc_init_holding(85, 3, "KPRCA", 7326279);
		
			cgc_init_holding(85, 4, "AAPL", 12665809);
		
			cgc_init_holding(85, 5, "OAK", 2397706);
		
			cgc_init_holding(85, 6, "DDTEK", 4294967295);
		
			cgc_init_holding(85, 7, "PALM", 5660432);
		
			cgc_init_holding(85, 8, "CROMU", 10432953);
		
			cgc_init_holding(85, 9, "PIRATE", 12261688);
		
			cgc_init_holding(85, 10, "MAPLE", 12782155);
		
			cgc_init_holding(86, 0, "GOOG", 9567690);
		
			cgc_init_holding(86, 1, "SK3WL", 4294967295);
		
			cgc_init_holding(86, 2, "NRFIN", 15521683);
		
			cgc_init_holding(86, 3, "KPRCA", 15940535);
		
			cgc_init_holding(86, 4, "AAPL", 3745123);
		
			cgc_init_holding(86, 5, "OAK", 2678419);
		
			cgc_init_holding(86, 6, "DDTEK", 1698777);
		
			cgc_init_holding(86, 7, "PALM", 10671356);
		
			cgc_init_holding(86, 8, "CROMU", 1393160);
		
			cgc_init_holding(86, 9, "PIRATE", 7388263);
		
			cgc_init_holding(86, 10, "MAPLE", 8568913);
		
			cgc_init_holding(87, 0, "GOOG", 16702215);
		
			cgc_init_holding(87, 1, "SK3WL", 9128904);
		
			cgc_init_holding(87, 2, "NRFIN", 5635369);
		
			cgc_init_holding(87, 3, "KPRCA", 15665003);
		
			cgc_init_holding(87, 4, "AAPL", 11689635);
		
			cgc_init_holding(87, 5, "OAK", 6718626);
		
			cgc_init_holding(87, 6, "DDTEK", 14856793);
		
			cgc_init_holding(87, 7, "PALM", 4294967295);
		
			cgc_init_holding(87, 8, "CROMU", 13131543);
		
			cgc_init_holding(87, 9, "PIRATE", 7093023);
		
			cgc_init_holding(87, 10, "MAPLE", 12546139);
		
			cgc_init_holding(88, 0, "GOOG", 8969934);
		
			cgc_init_holding(88, 1, "SK3WL", 4294967295);
		
			cgc_init_holding(88, 2, "NRFIN", 2934940);
		
			cgc_init_holding(88, 3, "KPRCA", 8910883);
		
			cgc_init_holding(88, 4, "AAPL", 3531946);
		
			cgc_init_holding(88, 5, "OAK", 15537263);
		
			cgc_init_holding(88, 6, "DDTEK", 2483600);
		
			cgc_init_holding(88, 7, "PALM", 6217737);
		
			cgc_init_holding(88, 8, "CROMU", 16624633);
		
			cgc_init_holding(88, 9, "PIRATE", 15306041);
		
			cgc_init_holding(88, 10, "MAPLE", 5975488);
		
			cgc_init_holding(89, 0, "GOOG", 14401400);
		
			cgc_init_holding(89, 1, "SK3WL", 2836599);
		
			cgc_init_holding(89, 2, "NRFIN", 10175949);
		
			cgc_init_holding(89, 3, "KPRCA", 2925119);
		
			cgc_init_holding(89, 4, "AAPL", 2570426);
		
			cgc_init_holding(89, 5, "OAK", 8634400);
		
			cgc_init_holding(89, 6, "DDTEK", 6959244);
		
			cgc_init_holding(89, 7, "PALM", 4294967295);
		
			cgc_init_holding(89, 8, "CROMU", 14143461);
		
			cgc_init_holding(89, 9, "PIRATE", 12596979);
		
			cgc_init_holding(89, 10, "MAPLE", 3518919);
		
			cgc_init_holding(90, 0, "GOOG", 13688486);
		
			cgc_init_holding(90, 1, "SK3WL", 10770343);
		
			cgc_init_holding(90, 2, "NRFIN", 13479577);
		
			cgc_init_holding(90, 3, "KPRCA", 3711162);
		
			cgc_init_holding(90, 4, "AAPL", 16061864);
		
			cgc_init_holding(90, 5, "OAK", 10855270);
		
			cgc_init_holding(90, 6, "DDTEK", 12291769);
		
			cgc_init_holding(90, 7, "PALM", 4294967295);
		
			cgc_init_holding(90, 8, "CROMU", 7482761);
		
			cgc_init_holding(90, 9, "PIRATE", 10481084);
		
			cgc_init_holding(90, 10, "MAPLE", 10474951);
		
			cgc_init_holding(91, 0, "GOOG", 11854170);
		
			cgc_init_holding(91, 1, "SK3WL", 1002800);
		
			cgc_init_holding(91, 2, "NRFIN", 9758578);
		
			cgc_init_holding(91, 3, "KPRCA", 10599882);
		
			cgc_init_holding(91, 4, "AAPL", 14373358);
		
			cgc_init_holding(91, 5, "OAK", 3491571);
		
			cgc_init_holding(91, 6, "DDTEK", 4294967295);
		
			cgc_init_holding(91, 7, "PALM", 8742348);
		
			cgc_init_holding(91, 8, "CROMU", 10194246);
		
			cgc_init_holding(91, 9, "PIRATE", 14896322);
		
			cgc_init_holding(91, 10, "MAPLE", 15584914);
		
			cgc_init_holding(92, 0, "GOOG", 2709273);
		
			cgc_init_holding(92, 1, "SK3WL", 4294967295);
		
			cgc_init_holding(92, 2, "NRFIN", 6682562);
		
			cgc_init_holding(92, 3, "KPRCA", 3447284);
		
			cgc_init_holding(92, 4, "AAPL", 9172244);
		
			cgc_init_holding(92, 5, "OAK", 7673008);
		
			cgc_init_holding(92, 6, "DDTEK", 7230331);
		
			cgc_init_holding(92, 7, "PALM", 11705022);
		
			cgc_init_holding(92, 8, "CROMU", 9207167);
		
			cgc_init_holding(92, 9, "PIRATE", 15335959);
		
			cgc_init_holding(92, 10, "MAPLE", 6256057);
		
			cgc_init_holding(93, 0, "GOOG", 6853876);
		
			cgc_init_holding(93, 1, "SK3WL", 4294967295);
		
			cgc_init_holding(93, 2, "NRFIN", 1481538);
		
			cgc_init_holding(93, 3, "KPRCA", 13172296);
		
			cgc_init_holding(93, 4, "AAPL", 14457233);
		
			cgc_init_holding(93, 5, "OAK", 9962927);
		
			cgc_init_holding(93, 6, "DDTEK", 14147388);
		
			cgc_init_holding(93, 7, "PALM", 12221322);
		
			cgc_init_holding(93, 8, "CROMU", 6393747);
		
			cgc_init_holding(93, 9, "PIRATE", 16596042);
		
			cgc_init_holding(93, 10, "MAPLE", 5943723);
		
			cgc_init_holding(94, 0, "GOOG", 11970548);
		
			cgc_init_holding(94, 1, "SK3WL", 8225578);
		
			cgc_init_holding(94, 2, "NRFIN", 3727297);
		
			cgc_init_holding(94, 3, "KPRCA", 6302378);
		
			cgc_init_holding(94, 4, "AAPL", 15614148);
		
			cgc_init_holding(94, 5, "OAK", 14270557);
		
			cgc_init_holding(94, 6, "DDTEK", 3765633);
		
			cgc_init_holding(94, 7, "PALM", 4294967295);
		
			cgc_init_holding(94, 8, "CROMU", 9647374);
		
			cgc_init_holding(94, 9, "PIRATE", 5053676);
		
			cgc_init_holding(94, 10, "MAPLE", 2402456);
		
			cgc_init_holding(95, 0, "GOOG", 12314570);
		
			cgc_init_holding(95, 1, "SK3WL", 4294967295);
		
			cgc_init_holding(95, 2, "NRFIN", 15021239);
		
			cgc_init_holding(95, 3, "KPRCA", 8283273);
		
			cgc_init_holding(95, 4, "AAPL", 5548686);
		
			cgc_init_holding(95, 5, "OAK", 15807611);
		
			cgc_init_holding(95, 6, "DDTEK", 16561606);
		
			cgc_init_holding(95, 7, "PALM", 11124284);
		
			cgc_init_holding(95, 8, "CROMU", 13590917);
		
			cgc_init_holding(95, 9, "PIRATE", 11378273);
		
			cgc_init_holding(95, 10, "MAPLE", 16135094);
		
			cgc_init_holding(96, 0, "GOOG", 1003383);
		
			cgc_init_holding(96, 1, "SK3WL", 4294967295);
		
			cgc_init_holding(96, 2, "NRFIN", 13581236);
		
			cgc_init_holding(96, 3, "KPRCA", 15529685);
		
			cgc_init_holding(96, 4, "AAPL", 12596233);
		
			cgc_init_holding(96, 5, "OAK", 10046791);
		
			cgc_init_holding(96, 6, "DDTEK", 5229777);
		
			cgc_init_holding(96, 7, "PALM", 13897105);
		
			cgc_init_holding(96, 8, "CROMU", 12115604);
		
			cgc_init_holding(96, 9, "PIRATE", 14707702);
		
			cgc_init_holding(96, 10, "MAPLE", 16634243);
		
			cgc_init_holding(97, 0, "GOOG", 3508084);
		
			cgc_init_holding(97, 1, "SK3WL", 8303761);
		
			cgc_init_holding(97, 2, "NRFIN", 12053208);
		
			cgc_init_holding(97, 3, "KPRCA", 1426317);
		
			cgc_init_holding(97, 4, "AAPL", 7446843);
		
			cgc_init_holding(97, 5, "OAK", 15625017);
		
			cgc_init_holding(97, 6, "DDTEK", 4294967295);
		
			cgc_init_holding(97, 7, "PALM", 8714698);
		
			cgc_init_holding(97, 8, "CROMU", 5724050);
		
			cgc_init_holding(97, 9, "PIRATE", 14289022);
		
			cgc_init_holding(97, 10, "MAPLE", 2516546);
		
			cgc_init_holding(98, 0, "GOOG", 5255555);
		
			cgc_init_holding(98, 1, "SK3WL", 8304671);
		
			cgc_init_holding(98, 2, "NRFIN", 6669642);
		
			cgc_init_holding(98, 3, "KPRCA", 3654473);
		
			cgc_init_holding(98, 4, "AAPL", 9432303);
		
			cgc_init_holding(98, 5, "OAK", 6476300);
		
			cgc_init_holding(98, 6, "DDTEK", 16520773);
		
			cgc_init_holding(98, 7, "PALM", 4294967295);
		
			cgc_init_holding(98, 8, "CROMU", 9705914);
		
			cgc_init_holding(98, 9, "PIRATE", 11793019);
		
			cgc_init_holding(98, 10, "MAPLE", 7968175);
		
			cgc_init_holding(99, 0, "GOOG", 10028966);
		
			cgc_init_holding(99, 1, "SK3WL", 15284950);
		
			cgc_init_holding(99, 2, "NRFIN", 9615739);
		
			cgc_init_holding(99, 3, "KPRCA", 10343294);
		
			cgc_init_holding(99, 4, "AAPL", 5544000);
		
			cgc_init_holding(99, 5, "OAK", 8899801);
		
			cgc_init_holding(99, 6, "DDTEK", 4294967295);
		
			cgc_init_holding(99, 7, "PALM", 14290409);
		
			cgc_init_holding(99, 8, "CROMU", 9381942);
		
			cgc_init_holding(99, 9, "PIRATE", 7062546);
		
			cgc_init_holding(99, 10, "MAPLE", 15755308);
		

}
