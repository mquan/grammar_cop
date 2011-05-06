require "#{File.dirname(__FILE__)}/../lib/grammar_cop"

puts dir = File.expand_path('../data', File.dirname(__FILE__))
GrammarCop::Dictionary.set_dictionary_path(dir)

dict = GrammarCop::Dictionary.create("en")
opts = GrammarCop::ParseOptions.create
GrammarCop::ParseOptions.set_short_length(opts, 7)
puts "short_length=#{GrammarCop::ParseOptions.get_short_length(opts)}"
GrammarCop::ParseOptions.set_linkage_limit(opts, 10)
puts "linkage limit=#{GrammarCop::ParseOptions.get_linkage_limit(opts)}"
text = "Grammar is useless because there's nothing to say -- Gertrude Stein."
sentence = GrammarCop::Sentence.create(text, dict)
puts num = GrammarCop::Sentence.parse(sentence, opts)
if num > 0
  linkage = GrammarCop::Linkage.create(0, sentence, opts)
  puts GrammarCop::Linkage.create_diagram(linkage)
  puts "sublinkages=#{GrammarCop::Linkage.sublinkages_count(linkage)}"
  puts "num_words=#{GrammarCop::Linkage.num_words_count(linkage)}"
  puts "num_links=#{GrammarCop::Linkage.num_links_count(linkage)}"
  GrammarCop::Linkage.destroy(linkage)
end

GrammarCop::Sentence.destroy(sentence)
GrammarCop::ParseOptions.destroy(opts)
GrammarCop::Dictionary.destroy(dict)
