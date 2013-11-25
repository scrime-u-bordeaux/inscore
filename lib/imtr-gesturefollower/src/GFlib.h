/**
 * @file   GFlib.h
 * @author Bruno Zamborlin
 * 
 * @brief  Gesture Follower, a tool for gesture analysis in real-time
 *
 * Copyright (C) 2008 by IRCAM-Centre Georges Pompidou, Paris, France.
 * 
 */


#ifndef   GFLIB
#define   GFLIB
#define	  GFLIBVERSION			"1.3.2 experimental"

//#define   TRACE_ON					/*	debug on					*/
#ifdef TRACE_ON
#include  "GFCodeTrace.h"				/*	debugging					*/
#endif

#include  <stdexcept>					/*  exception, runtime_error	*/
#include  <sstream>						/*	debugging					*/
#include  "GFlibUtility.h"				/*	Math utilities				*/
#include  "GFphrase.h"					/*  GF phrase                   */
#include  "GFclient.h"					/*  GFclient virtual class definition	*/

#ifdef WIN32
#define isnan(x) ((x) != (x))
//#define DEBUG_CLIENTBLOCK new(_CLIENT_BLOCK, __FILE__, __LINE__)
#endif

#define MAX_DEFAULT_ALLOC_CHANNELS	64
#define GFDEFAULTFRAMEPERIOD        20
#define INF std::numeric_limits<float>::infinity()
using namespace std;


/* class declarations */

class Phrase;
class GFClient;



/***********************			GFexception CLASS		********************/

class GFexception : public exception{
public:
  virtual const char* what() const throw(){
	return "exception";
  }
};




/***********************			GESTURE CLASS		********************/

class GF {
  
  friend class Phrase;	//Phrase class needs to access to private field of GF
  
public:	
  
  #pragma mark -
  #pragma mark Static
  static const float  AUTORESTART_AMOUNT;	/*  used in the autoRestart() method   */
  static const int	  MAXSPEED;
  static const int	  FIRST;
  static const int	  ANY;
  static const int	  MAHAL;
  static const int	  KL;
  static const int	  MAXSCENES;
  static const float  SCORE_TH;	/*	the threshold to convert a float into a boolen in the score  */
  static const int	  LH_MIN;
  static const int	  MAX_REGIONS;		/* the maximum number of regions for each phrase	*/
  
  GFClient* client;
  
  #pragma mark -
  #pragma mark Memory
  
  int     maxPhrases;           // number of allocated phrases
  int     maxChannels; // max number of allocated channels for each phrase 
  int     channels;			//number of allocated channels for each phrase
  long    defaultMaxFrames;			// the default max capacity of phrases
  int     maxLearnedPhrasesIndex;  //the highest learned phrase index
  void    updateMaxLearnedPhraseIndex();
  bool    setMaxPhrases(int nPhrases, float **BMeans, float **probability, int *sizes, int *capacity); //set the number of max phrases with a given external memory pointer (NULL for allocating memory internally)
  void    setMaxFrames(int mf);
  void    setChannels(int ch);
  void    setMaxChannels(int max);
  
  bool    isLearning;             // true if GF is in learning mode
  int     learningPhrase;			// the index of the phrase that has being recorded (in [0, maxPhrases-1])
  bool    scoreAllocatedInternally;
  bool    BMeanAllocatedInternally;
  
  void			setLearningOff () ;		//= learn off
  void			setLearning(int phrase_idx);
  void			setLearning(int phrase_idx,int example_idx);
  void			setLearning(int phrase_idx,int example_idx, std::string name);
  void			setDecoding(int);
  
  void			clear(int phrase_idx);		//clear learning and decoding data of all examples of the given phrase
  void			clear(int phrase_idx,	int example_idx);
  void			clear(std::string name,		int example_idx);
  void			clearAll();					// clear all
  void			clear(std::string name);			//clear a phrase specified by its name
  
  
  #pragma mark -
  #pragma mark Transport

  bool isDecoding;	// true if GF is in decoding mode
  bool isPlaying;		// true if GF is in play mode (no following)
  bool isPaused;		// true if GF is in pause mode
  int	markerOffset;	// global marker offset
  
  void restart(int phrase_idx);	      //reset any decoding data of the given phrase
  void restartAll();				          //reset any decoding data of all phrases
  void goTo(int phrase_idx, int pos);	//goto a specified index
  void setMarkerOffset(int offset);	  //setting the global marker offset
  void play(float speed);			        //set the play mode
  
  
  #pragma mark -
  #pragma mark Performance
  
  int		likelihoodWindowSize;	// the size of the window that contains the history of the likelihoods (how fast the "likelihoods"	will change)
  bool      isLikelihoodWindowNorm; //true if likelihoodwindow has been set as percentage (then it changes dinamically)
  float     likelihoodWindowPercentage;
  int		smoothingSpeed;         // the size of the window that contains the history of the speeds (how fast the "speed"	will change)
  int		beginning;              // initialization type:  "first"-> alfa = [1,0 ... 0] , "any" -> alfa = [1/L ... 1/L]
  int		metric;                 // "Mahalanobis" or "Kullback-Leibler"
  float*	weights;                // the weight of each channel (in [0,1])
  float		likelihoodContrast;     // contrast between normalized likelihoods
  int		autorestart;
  int		windowSize;
  bool  autoTimeTag;                    // if true, the first float of the observation is considered as a timetag (false by default)
  int		autoRestartLimit;		// a phrase is considered "ended" when its index is greater than "end - autoRestartLimit"
  float		tolerance;				// global tolerance
  bool      forward;                // forward option (index doesn't go back)
  bool      viterbi;
  float*	expectedSpeed;			/*	vector for expected probability. its size is "MAXSPEED"                         */
  
  void		setMetric(int);
  void		setBeginning(int);
  void		setTolerance(float);
  void		setSmoothingSpeed(int);
  void		setLikelihoodWindow(int);
  void      setLikelihoodWindowNorm(float percentage); //set likelihoodwindow as percentage of the longest phrase
  void		setWeights(float* weights,int size);
  void		setWeights(double* weights,int size);
  void		setLikelihoodContrast(float);
  void		setWindowSize(int size);
  void		setChannelName(int id, std::string name);
  void		setChannelNames(std::string* names, int size);
  void		setFramePeriod(float fp);
  void		setName(int index, std::string name);
  void		setAutoRestart(int i);
  void		setExpectedSpeed(float*);
  void      setViterbi(bool b);
  void      setForward(bool b);
  
  #pragma mark -
  #pragma mark Normalization

  void      normalizeAllPhrases();  // update minObs and maxObs to the global min and max of all phrases. all observations will be scaled between these values
  float*    minObs;
  float*    maxObs;
  float*    rangeObs;
  bool      normalization;          //normalization on/off
  void      setNormalization(bool);
  void      setMinMax(int channelIndex, float min, float max);
  void      normalizeObs(float* obs, int size);
  
  
  #pragma mark -
  #pragma mark Score

  bool		sceneEnable;			//if the scenes are enabled or not (false by default)
  void		enable(int* phraseList, int size);			
  void      enableone(int i, bool b);  //enable this phrase without changing the others
  float***	score;					// the probability matrix to go from a phrase to another. size: [maxScene][maxPhrases][maxPhrases]
  int		scene;					// the current scene
  
  void		setScene(int scene);									//set the current scene
  //int		setScore(int scene, float** probabilityMatrix);		//Requirements: probabilityMatrix has to be a float[maxPhrases][maxPhrases]
  void		transition(int scene, int row, int col, float value);		//Useful with the "matrixctrl" object of MaxMSP
  void		initScore();											// init score to default
  void		nextScene();
  
  
  /*	Results	(pointers to results of each phrase) */
  #pragma mark -
  #pragma Results

  int*		index;					// où on est dans le geste (frames)
  float*	n_index;				// index normalizé entre 0 et 1
  float*	likelihood;				// log d'une probabilité de -min (-30 à vérifier) à  0
  float*	n_likelihood;			// probablilité normalisée entre toutes les phrases (somme = 1)
  float*	speed;					// vitesse de lecture du geste (index_i - index_(i-1) )
  
  
  /*	Internal fields 	*/
  int	likeliest;					// the index of the likeliest phrase
  std::string	errorDescr;
  
  float	frameperiod;						// current sample period
  std::string*	channelName;		// name of channels
  int		freezeLikelihoodAmount;
  
  
  /*	Phrases 	*/
  Phrase**	phrase;               // an array of "maxPhrases" references of each Phrase	
  
  /***	CLASS CONSTRUCTOR	***/
  /*  requirements:
   BMeans_ must be a float pointer of a two dimensional preallocated array [maxPhrases_][channels_*capacity_] 
   n_index_, likelihood_, speed_ and marker_ must be preallocated arrays [maxPhrases][1]
   score_ must be preallocated array [MAXSCENES][maxPhrases_][maxPhrases_]
   */
  GF(GFClient* parent, int maxPhrases_,	int maxChannels, long capacity_,	float** BMeans_, float** alfa_, float*** score_);
  
  /*  deconstructor  */
  ~GF();
  
  
  /***	HMM			***/
  #pragma mark -
  #pragma mark HMM

  void	  observation(float* Obs, int size, bool normalize=false);	//Obs is the incoming observation
  void	  decoding	(float* Obs, Phrase* p, bool normalize=false);  //do the decoding of Obs
  void	  calculateLikeliest();				//calculate the likeliest
  void	  normalizeLikelihoods();			//normalize the list of likelihoods, applying normalization and contrast
  void	  autoRestart();
  
  void updatePhraseTimeTags(int phraseIndex, float* tg, int size); //update timetags from data
  void updatePhraseMemory(float* _BMean, float* _alfa, int size, int maxFrames, int phraseIndex);
  
  /***	DEBUGGING METHODS	***/
  void	  getAlfa	(int idx, float* &alfa, int &size);		//return alfa, its offset and size
  std::string  postV(float* f, int start, int end, int size);	//add a std::string representation of f in the debugger
  
  
};




#endif // GFlib_H
