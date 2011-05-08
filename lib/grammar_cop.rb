$: << File.dirname(__FILE__)
require 'grammar_cop/dictionary'
require 'grammar_cop/parse_options'
require 'grammar_cop/sentence'
require 'grammar_cop/linkage'

module GrammarCop
  GrammarCop::Dictionary.set_dictionary_path("#{Gem.loaded_specs['grammar_cop'].full_gem_path}/data")
end
