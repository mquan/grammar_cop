#include "link-grammar/api.h"
#include "link-grammar/api.c" //need ifndef
#include "link-grammar/analyze-linkage.h"
#include "link-grammar/analyze-linkage.c"
#include "link-grammar/and.h"
#include "link-grammar/and.c"
#include "link-grammar/build-disjuncts.h"
#include "link-grammar/build-disjuncts.c"
#include "link-grammar/count.h"
#include "link-grammar/count.c"
#include "link-grammar/disjunct-utils.h" //ifndef guard
#include "link-grammar/disjunct-utils.c"
#include "link-grammar/disjuncts.h"
#include "link-grammar/disjuncts.c"
#include "link-grammar/error.h"
#include "link-grammar/error.c"
#include "link-grammar/extract-links.h"
#include "link-grammar/extract-links.c"
#include "link-grammar/fast-match.h"
#include "link-grammar/fast-match.c"
#include "link-grammar/idiom.h"
#include "link-grammar/idiom.c" //rename is_number to is_number_idiom line 61 and 82 (same function name as tokenize)
#include "link-grammar/massage.h"
#include "link-grammar/massage.c"
#include "link-grammar/pp_knowledge.h"
#include "link-grammar/pp_knowledge.c"
#include "link-grammar/pp_lexer.h"
#include "link-grammar/pp_lexer.c"
#include "link-grammar/pp_linkset.h"
#include "link-grammar/pp_linkset.c"
#include "link-grammar/post-process.h"
#include "link-grammar/post-process.c"
#include "link-grammar/preparation.h"
#include "link-grammar/preparation.c"
#include "link-grammar/print-util.h"
#include "link-grammar/print-util.c"
#include "link-grammar/print.h"
#include "link-grammar/print.c"
#include "link-grammar/prune.h"
#include "link-grammar/prune.c" //comment out line 20 to 27 (same as disjunct-util line87). Can also use ifndef
#include "link-grammar/resources.h"
#include "link-grammar/resources.c"
#include "link-grammar/read-dict.h"
#include "link-grammar/read-dict.c"
#include "link-grammar/read-regex.h"
#include "link-grammar/read-regex.c"
#include "link-grammar/regex-morph.h"
#include "link-grammar/regex-morph.c"
#include "link-grammar/string-set.h"
#include "link-grammar/string-set.c"
#include "link-grammar/tokenize.h"
#include "link-grammar/tokenize.c" //put ifndef around spellcheck.h
#include "link-grammar/utilities.h" //define DICTIONARY_DIR "../../../data/"
#include "link-grammar/utilities.c"
#include "link-grammar/word-utils.h"
#include "link-grammar/word-utils.c"
#include "link-grammar/word-file.h"
#include "link-grammar/word-file.c"

#include "ruby.h"

//pointer wrappers containing Dictionary, Parse_Options, Sentence objects
struct dictionary_ptr {
	Dictionary dict;
};

struct parse_options_ptr {
	Parse_Options opts;
};

struct sentence_ptr {
	Sentence sentence;
};

struct linkage_ptr {
	Linkage linkage;
};

void dictionary_path_set(const VALUE self, volatile VALUE dict_path);
struct dictionary_ptr *create_dictionary(const VALUE self, volatile VALUE lang);
void delete_dictionary(const VALUE self, struct dictionary_ptr *ptr);

struct parse_options_ptr *create_parse_options(const VALUE self);
VALUE delete_parse_options(const VALUE self, struct parse_options_ptr *ptr);
void linkage_limit_set(const VALUE self, struct parse_options_ptr *ptr, volatile VALUE limit);
VALUE linkage_limit_get(const VALUE self, struct parse_options_ptr *ptr);
void short_length_set(const VALUE self, struct parse_options_ptr *ptr, volatile VALUE length);
VALUE short_length_get(const VALUE self, struct parse_options_ptr *ptr);

struct sentence_ptr *create_sentence(const VALUE self, volatile VALUE str, struct dictionary_ptr *dict_ptr);
VALUE parse_sentence(const VALUE self, struct sentence_ptr *sentence, struct parse_options_ptr *opts_ptr);
void delete_sentence(const VALUE self, struct sentence_ptr *sentence);

struct linkage_ptr *create_linkage(const VALUE self, volatile VALUE k, struct sentence_ptr *sent_ptr, struct parse_options_ptr *opts_ptr);
void delete_linkage(const VALUE self, struct linkage_ptr *link_ptr);
VALUE print_linkage_diagram(const VALUE self, struct linkage_ptr *link_ptr);
VALUE linkage_count_sublinkages(const VALUE self, struct linkage_ptr *link_ptr);
VALUE linkage_count_num_words(const VALUE self, struct linkage_ptr *link_ptr);
VALUE linkage_count_num_links(const VALUE self, struct linkage_ptr *link_ptr);