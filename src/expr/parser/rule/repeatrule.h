#pragma once

#include "rule.h"

namespace Rules {

	template<typename... Elements>
	class Repeat : public Rule {

	public:
		static inline const QString description = QStringLiteral("( %1 )+").arg(QStringList{Elements::description...}.join(", "));

	public:
		static RuleSP parse(Parser &p) {
			using F = RuleSP (*)(Parser &);
			static const F parseFuncs[] = {+[](Parser &p) { return Elements::parse(p); }...};

			QList<RuleSP> allRules;
			std::vector<Rec> recs;

			RuleSP err = [&] {
				while(true) {
					QList<RuleSP> rules;
					for(const auto &parsef: parseFuncs) {
						RuleSP r = parsef(p);
						if(r->isErrorRule())
							return r;

						p.skipWhitespace();
						rules += r;
					}

					qsizetype i = 0;
					recs.push_back(Rec{static_cast<const Elements & > (*rules.at(i++))...});
					allRules += rules;
				}

				return RuleSP{};
			}();

			if(recs.empty()) {
				assert(err);
				return err;
			}

			auto r = std::make_shared<Repeat>();
			r->recs.swap(recs);
			r->rules.swap(allRules);
			return r;
		}

	public:
		using Rec = std::tuple<const Elements &...>;

		/// Rules arranged into a nice rec list
		std::vector<Rec> recs;

		/// Used rules
		QList<RuleSP> rules;

	};

}
