#include <locale.h>
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <math.h>

#include "link_grammar.h"

void Init_link_grammar() {
	VALUE lg = rb_define_module("LinkGrammar");
	rb_define_module_function(lg, "create_dictionary", create_dictionary, 1);
	rb_define_module_function(lg, "delete_dictionary", delete_dictionary, 1);
	rb_define_module_function(lg, "dictionary_path_set", dictionary_path_set, 1);
	rb_define_module_function(lg, "create_parse_options", create_parse_options, 0);
	rb_define_module_function(lg, "delete_parse_options", delete_parse_options, 1);
	rb_define_module_function(lg, "linkage_limit_set", linkage_limit_set, 2);
	rb_define_module_function(lg, "linkage_limit_get", linkage_limit_get, 1);
	rb_define_module_function(lg, "short_length_set", short_length_set, 2);
	rb_define_module_function(lg, "short_length_get", short_length_get, 1);
	rb_define_module_function(lg, "create_sentence", create_sentence, 2);
	rb_define_module_function(lg, "parse_sentence", parse_sentence, 2);
	rb_define_module_function(lg, "delete_sentence", delete_sentence, 1);
	rb_define_module_function(lg, "create_linkage", create_linkage, 3);
	rb_define_module_function(lg, "delete_linkage", delete_linkage, 1);
	rb_define_module_function(lg, "print_linkage_diagram", print_linkage_diagram, 1);
	rb_define_module_function(lg, "linkage_count_sublinkages", linkage_count_sublinkages, 1);
	rb_define_module_function(lg, "linkage_count_num_words", linkage_count_num_words, 1);
	rb_define_module_function(lg, "linkage_count_num_links", linkage_count_num_links, 1);
}

void dictionary_path_set(const VALUE self, VALUE dict_path) {
	char *pathstr = StringValuePtr(dict_path);
	dictionary_set_data_dir(pathstr);
}

struct dictionary_ptr *create_dictionary(const VALUE self, volatile VALUE lang) {
	Dictionary dict = dictionary_create_lang(StringValuePtr(lang));
	struct dictionary_ptr *ptr = ALLOC(struct dictionary_ptr);
	ptr->dict = NULL;
	ptr->dict = dict;
	return ptr;
}

void delete_dictionary(const VALUE self, struct dictionary_ptr *ptr) {
	dictionary_delete(ptr->dict);
	ptr = NULL;
}

struct parse_options_ptr *create_parse_options(const VALUE self) {
	Parse_Options options = parse_options_create();
	struct parse_options_ptr *ptr = ALLOC(struct parse_options_ptr);
	ptr->opts = NULL;
	ptr->opts = options;
	return ptr;
}

VALUE delete_parse_options(const VALUE self, struct parse_options_ptr *ptr) {
	int a = parse_options_delete(ptr->opts);
	ptr = NULL;
	return INT2FIX(a);
}

void linkage_limit_set(const VALUE self, struct parse_options_ptr *ptr, volatile VALUE limit) {
	int l = NUM2INT(limit);
	parse_options_set_linkage_limit(ptr->opts, l);
}

VALUE linkage_limit_get(const VALUE self, struct parse_options_ptr *ptr) {
	int l = parse_options_get_linkage_limit(ptr->opts);
	return INT2FIX(l);
}

void short_length_set(const VALUE self, struct parse_options_ptr *ptr, volatile VALUE length) {
	int l = NUM2INT(length);
	parse_options_set_short_length(ptr->opts, l);
}

VALUE short_length_get(const VALUE self, struct parse_options_ptr *ptr) {
	int l = parse_options_get_short_length(ptr->opts);
	return INT2FIX(l);
}

struct sentence_ptr *create_sentence(const VALUE self, volatile VALUE str, struct dictionary_ptr *dict_ptr) {
	char *text = StringValuePtr(str);
	Sentence sentence = sentence_create(text, dict_ptr->dict);
	struct sentence_ptr *sent_ptr = ALLOC(struct sentence_ptr);
	sent_ptr->sentence = NULL;
	sent_ptr->sentence = sentence;
	return sent_ptr;
}

VALUE parse_sentence(const VALUE self, struct sentence_ptr *sent_ptr, struct parse_options_ptr *opts_ptr) {
	int num_linkages = sentence_parse(sent_ptr->sentence, opts_ptr->opts);
	return INT2FIX(num_linkages);
}

void delete_sentence(const VALUE self, struct sentence_ptr *ptr) {
	sentence_delete(ptr->sentence);
	ptr = NULL;
}

struct linkage_ptr *create_linkage(const VALUE self, volatile VALUE k, struct sentence_ptr *sent_ptr, struct parse_options_ptr *opts_ptr) {
	int ck = NUM2INT(k);
	Linkage linkage = linkage_create(ck, sent_ptr->sentence, opts_ptr->opts);
	struct linkage_ptr *link_ptr = ALLOC(struct linkage_ptr);
	link_ptr->linkage = NULL;
	link_ptr->linkage = linkage;
	return link_ptr;
}

void delete_linkage(const VALUE self, struct linkage_ptr *link_ptr) {
	linkage_delete(link_ptr->linkage);
	link_ptr = NULL;
}

VALUE print_linkage_diagram(const VALUE self, struct linkage_ptr *link_ptr) {
	char *diagram = linkage_print_diagram(link_ptr->linkage);
	return rb_str_new2(diagram);
}

VALUE linkage_count_sublinkages(const VALUE self, struct linkage_ptr *link_ptr) {
	int cnt = linkage_get_num_sublinkages(link_ptr->linkage);
	return INT2FIX(cnt);
}

VALUE linkage_count_num_words(const VALUE self, struct linkage_ptr *link_ptr) {
	int cnt = linkage_get_num_words(link_ptr->linkage);
	return INT2FIX(cnt);
}

VALUE linkage_count_num_links(const VALUE self, struct linkage_ptr *link_ptr) {
	int cnt = linkage_get_num_links(link_ptr->linkage);
	return INT2FIX(cnt);
}