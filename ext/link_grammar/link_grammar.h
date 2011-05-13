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
typedef struct dictionary_ptr {
	Dictionary dict;
} DictionaryPtr;

typedef struct parse_options_ptr {
	Parse_Options opts;
} ParseOptionsPtr;

typedef struct sentence_ptr {
	Sentence sentence;
} SentencePtr;

typedef struct linkage_ptr {
	Linkage linkage;
} LinkagePtr;

VALUE dictionary_path_set(const VALUE self, volatile VALUE dict_path);
VALUE create_dictionary(const VALUE self, volatile VALUE lang);
VALUE delete_dictionary(const VALUE self, VALUE dict);

VALUE create_parse_options(const VALUE self);
VALUE delete_parse_options(const VALUE self, VALUE opts);
VALUE linkage_limit_set(const VALUE self, VALUE opts, volatile VALUE limit);
VALUE linkage_limit_get(const VALUE self, VALUE opts);
VALUE short_length_set(const VALUE self, VALUE opts, volatile VALUE length);
VALUE short_length_get(const VALUE self, VALUE opts);
VALUE disjunct_cost_set(const VALUE self, VALUE opts, volatile VALUE cost);
VALUE disjunct_cost_get(const VALUE self, VALUE opts);
VALUE min_null_count_set(const VALUE self, VALUE opts, volatile VALUE count);
VALUE min_null_count_get(const VALUE self, VALUE opts);
VALUE max_null_count_set(const VALUE self, VALUE opts, volatile VALUE count);
VALUE max_null_count_get(const VALUE self, VALUE opts);
VALUE options_null_block_set(const VALUE self, VALUE opts, volatile VALUE n_block);
VALUE options_null_block_get(const VALUE self, VALUE opts);
VALUE islands_ok_set(const VALUE self, VALUE opts, volatile VALUE islands_ok);
VALUE islands_ok_get(const VALUE self, VALUE opts);

VALUE create_sentence(const VALUE self, volatile VALUE str, VALUE dict);
VALUE parse_sentence(const VALUE self, VALUE sentence, VALUE opts);
VALUE delete_sentence(const VALUE self, VALUE sentence);

VALUE create_linkage(const VALUE self, volatile VALUE k, VALUE sentence, VALUE opts);
VALUE delete_linkage(const VALUE self, VALUE link);
VALUE print_linkage_diagram(const VALUE self, VALUE link);
VALUE linkage_count_sublinkages(const VALUE self, VALUE link);
VALUE linkage_count_num_words(const VALUE self, VALUE link);
VALUE linkage_count_num_links(const VALUE self, VALUE link);