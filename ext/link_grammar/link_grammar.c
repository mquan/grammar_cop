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

//functions for retrieving pointers from ruby VALUE wrapper
DictionaryPtr *retrieve_dictionary(VALUE dict) {
	DictionaryPtr *ptr;
	Data_Get_Struct(dict, DictionaryPtr, ptr);
	return ptr;
}

ParseOptionsPtr *retrieve_parse_options(VALUE opts) {
	ParseOptionsPtr *ptr;
	Data_Get_Struct(opts, ParseOptionsPtr, ptr);
	return ptr;
}

SentencePtr *retrieve_sentence(VALUE sentence) {
	SentencePtr *ptr;
	Data_Get_Struct(sentence, SentencePtr, ptr);
	return ptr;
}

LinkagePtr *retrieve_linkage(VALUE link) {
	LinkagePtr *ptr;
	Data_Get_Struct(link, LinkagePtr, ptr);
	return ptr;
}

//custom routines for freeing memory pointers
void free_dictionary_ptr(DictionaryPtr *ptr) {
	dictionary_delete(ptr->dict);
	free(ptr);
}

void free_parse_options_ptr(ParseOptionsPtr *ptr) {
	parse_options_delete(ptr->opts);
	free(ptr);
}

void free_sentence_ptr(SentencePtr *ptr) {
	sentence_delete(ptr->sentence);
	free(ptr);
}

void free_linkage_ptr(LinkagePtr *ptr) {
	linkage_delete(ptr->linkage);
	free(ptr);
}

VALUE dictionary_path_set(const VALUE self, VALUE dict_path) {
	char *pathstr = StringValuePtr(dict_path);
	dictionary_set_data_dir(pathstr);
	return Qnil;
}

VALUE create_dictionary(const VALUE self, volatile VALUE lang) {
	Dictionary dict = dictionary_create_lang(StringValuePtr(lang));
	DictionaryPtr *ptr = ALLOC(DictionaryPtr);
	ptr->dict = NULL;
	ptr->dict = dict;
	return Data_Wrap_Struct(self, 0, free_dictionary_ptr, ptr);
}

VALUE delete_dictionary(const VALUE self, VALUE dict) {
	DictionaryPtr *ptr = retrieve_dictionary(dict);
	free_dictionary_ptr(ptr);
	return Qnil;
}

VALUE create_parse_options(const VALUE self) {
	Parse_Options options = parse_options_create();
	ParseOptionsPtr *ptr = ALLOC(ParseOptionsPtr);
	ptr->opts = NULL;
	ptr->opts = options;
	return Data_Wrap_Struct(self, 0, free_parse_options_ptr, ptr);
}

VALUE delete_parse_options(const VALUE self, VALUE opts) {
	ParseOptionsPtr *ptr = retrieve_parse_options(opts);
	//int a = parse_options_delete(ptr->opts);
	free_parse_options_ptr(ptr);
	//return INT2FIX(a);
	return Qnil;
}

VALUE linkage_limit_set(const VALUE self, VALUE opts, volatile VALUE limit) {
	ParseOptionsPtr *ptr = retrieve_parse_options(opts);
	int l = NUM2INT(limit);
	parse_options_set_linkage_limit(ptr->opts, l);
	return Qnil;
}

VALUE linkage_limit_get(const VALUE self, VALUE opts) {
	ParseOptionsPtr *ptr = retrieve_parse_options(opts);
	int l = parse_options_get_linkage_limit(ptr->opts);
	return INT2FIX(l);
}

VALUE short_length_set(const VALUE self, VALUE opts, volatile VALUE length) {
	ParseOptionsPtr *ptr = retrieve_parse_options(opts);
	int l = NUM2INT(length);
	parse_options_set_short_length(ptr->opts, l);
	return Qnil;
}

VALUE short_length_get(const VALUE self, VALUE opts) {
	ParseOptionsPtr *ptr = retrieve_parse_options(opts);
	int l = parse_options_get_short_length(ptr->opts);
	return INT2FIX(l);
}

VALUE create_sentence(const VALUE self, volatile VALUE str, VALUE dict) {
	char *text = StringValuePtr(str);
	DictionaryPtr *dict_ptr = retrieve_dictionary(dict);
	Sentence sentence = sentence_create(text, dict_ptr->dict);
	SentencePtr *sent_ptr = ALLOC(SentencePtr);
	sent_ptr->sentence = NULL;
	sent_ptr->sentence = sentence;
	return Data_Wrap_Struct(self, 0, free, sent_ptr);
}

VALUE parse_sentence(const VALUE self, VALUE sentence, VALUE opts) {
	SentencePtr *sent_ptr = retrieve_sentence(sentence);
	ParseOptionsPtr *opts_ptr = retrieve_parse_options(opts);
	int num_linkages = sentence_parse(sent_ptr->sentence, opts_ptr->opts);
	return INT2FIX(num_linkages);
}

VALUE delete_sentence(const VALUE self, VALUE sentence) {
	SentencePtr *ptr = retrieve_sentence(sentence);
	sentence_delete(ptr->sentence);
	//free_sentence_ptr(ptr);
	return Qnil;
}

VALUE create_linkage(const VALUE self, volatile VALUE k, VALUE sentence, VALUE opts) {
	int ck = NUM2INT(k);
	SentencePtr *sent_ptr = retrieve_sentence(sentence);
	ParseOptionsPtr *opts_ptr = retrieve_parse_options(opts);
	Linkage linkage = linkage_create(ck, sent_ptr->sentence, opts_ptr->opts);
	LinkagePtr *link_ptr = ALLOC(LinkagePtr);
	link_ptr->linkage = NULL;
	link_ptr->linkage = linkage;
	return Data_Wrap_Struct(self, 0, free_linkage_ptr, link_ptr);
}

VALUE delete_linkage(const VALUE self, VALUE link) {
	LinkagePtr *link_ptr = retrieve_linkage(link);
	free_linkage_ptr(link_ptr);
	return Qnil;
}

VALUE print_linkage_diagram(const VALUE self, VALUE link) {
	LinkagePtr *link_ptr = retrieve_linkage(link);
	char *diagram = linkage_print_diagram(link_ptr->linkage);
	return rb_str_new2(diagram);
}

VALUE linkage_count_sublinkages(const VALUE self, VALUE link) {
	LinkagePtr *link_ptr = retrieve_linkage(link);
	int cnt = linkage_get_num_sublinkages(link_ptr->linkage);
	return INT2FIX(cnt);
}

VALUE linkage_count_num_words(const VALUE self, VALUE link) {
	LinkagePtr *link_ptr = retrieve_linkage(link);
	int cnt = linkage_get_num_words(link_ptr->linkage);
	return INT2FIX(cnt);
}

VALUE linkage_count_num_links(const VALUE self, VALUE link) {
	LinkagePtr *link_ptr = retrieve_linkage(link);
	int cnt = linkage_get_num_links(link_ptr->linkage);
	return INT2FIX(cnt);
}