# -*- encoding: utf-8 -*-
$:.push File.expand_path("../lib", __FILE__)
require "grammar_cop/version"

Gem::Specification.new do |s|
  s.name        = "grammar_cop"
  s.version     = GrammarCop::VERSION
  s.platform    = Gem::Platform::RUBY
  s.extensions  = ["ext/link_grammar/extconf.rb"]
  s.authors     = ["Quan Nguyen"]
  s.email       = ["mquannie@gmail.com"]
  s.homepage    = "https://github.com/mquan"
  s.summary     = %q{a C extension for the link-grammar-4.7.4 library}
  s.description = %q{This gem uses link-grammar's dictionary and parser to determine if a sentence is grammatically correct}

  s.rubyforge_project = "grammar_cop"

  s.files         = `git ls-files`.split("\n")
  s.test_files    = `git ls-files -- {test,spec,features}/*`.split("\n")
  s.executables   = `git ls-files -- bin/*`.split("\n").map{ |f| File.basename(f) }
  s.require_paths = ["lib"]
  
  s.add_dependency(%q<rake-compiler>)
end
