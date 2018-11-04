#include "Input.h"

/*
 *  public methods
 */

Input::Input(Config& config, Vocab& vocab, vector<string>& bucket)
{
  this->max_sentence_length = bucket.size();

  // create input tensors
  tensorflow::TensorShape shape1({1, this->max_sentence_length});
  this->sentence_word_ids = new tensorflow::Tensor(tensorflow::DT_FLOAT, shape1);
  tensorflow::TensorShape shape2({1, this->max_sentence_length, config.GetWordLength()});
  this->sentence_wordchr_ids = new tensorflow::Tensor(tensorflow::DT_FLOAT, shape2);
  this->sentence_pos_ids = new tensorflow::Tensor(tensorflow::DT_FLOAT, shape1);
  tensorflow::TensorShape shape3({1, this->max_sentence_length, config.GetEtcDim()});
  this->sentence_etcs = new tensorflow::Tensor(tensorflow::DT_FLOAT, shape3);
  
  for( int i=0; i < max_sentence_length; i++ ) {
    string line = bucket[i];
    vector<string> tokens;
    vocab.Split(line, tokens);
    if( tokens.size() != 4 ) {
      throw runtime_error("input tokens must be size 4");
    }
    string word  = tokens[0];
    string pos   = tokens[1];
    string chunk = tokens[2];
    string tag   = tokens[3];
    // build sentence_word_ids
    int wid = vocab.GetWid(word);
    auto data_ = this->sentence_word_ids->flat<float>().data();
    data_[i] = wid;
    // build sentence_wordchr_ids
    // build sentence_pos_ids
    // build sentence_etcs
    
  }
}

Input::~Input()
{
  if( this->sentence_word_ids ) delete this->sentence_word_ids;
  if( this->sentence_wordchr_ids ) delete this->sentence_wordchr_ids;
  if( this->sentence_pos_ids ) delete this->sentence_pos_ids;
  if( this->sentence_etcs ) delete this->sentence_etcs;
}

