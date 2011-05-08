require 'grammar_cop/link_grammar'

module GrammarCop
  class Sentence
    extend LinkGrammar
    def self.create(text, dictionary)
      create_sentence(text, dictionary)
    end

    def self.parse(sentence, options)
      parse_sentence(sentence, options)
    end
    
    def self.destroy(sentence)
      delete_sentence(sentence)
    end
    
    def self.count_linkages(text, dictionary, options)
      count = 0
      #split sentence up by punctuation to reduce processing time
      text.split(/[\!?,;:']+/).each do |clause|
        c = create_sentence(clause, dictionary)
        count += parse_sentence(c, options)
        delete_sentence(c)
      end
      
      #however, sometimes the split results in all incomplete clause so check one more time in those cases
      if count == 0
        s = create_sentence(text, dictionary)
        count = parse_sentence(s, options)
        delete_sentence(s)
      end
      count
    end
  end
end