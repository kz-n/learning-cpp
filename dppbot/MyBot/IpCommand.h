#pragma once

#include <iostream>
#include <string>
#include <dpp/dpp.h>
#include <json.hpp>
#include "HTTPRequest.hpp"
using namespace std;
namespace IpCommand {
    static string getStringJson(json j) {
        auto cpp_string = j.template get<std::string>();
        // retrieve the string value (alternative when a variable already exists)
        std::string cpp_string2;
        j.get_to(cpp_string2);
        return cpp_string;
    }

    static void execute(const dpp::slashcommand_t& event, string ip) {
        try {
            http::Request request{"http://ip-api.com/json/" + ip};

            const auto response = request.send("GET");

            string sResponse = std::string{ response.body.begin(), response.body.end() };

            json jResponse = json::parse(sResponse);
            

            dpp::embed embed = dpp::embed().
                set_color(dpp::colors::sti_blue).
                set_author("IP Lookup", "", "");

            if (jResponse["status"] == "success") {
                embed.set_title(getStringJson(jResponse["query"])).
                    set_description(to_string(jResponse["lat"]) + " " +
                        to_string(jResponse["lon"]) + ", " + getStringJson(jResponse["country"]) + " " + getStringJson(jResponse["regionName"])).
                    add_field("City", getStringJson(jResponse["city"]) + ", " + getStringJson(jResponse["zip"])).
                    add_field("ISP", getStringJson(jResponse["isp"]) + " (" + getStringJson(jResponse["org"]) + ")");
            }
            dpp::message msg;
            msg.add_embed(embed);
            event.reply(msg);
        }
        catch (const std::exception& e) {
            std::cerr << "Request failed, error: " << e.what() << '\n';
        }
	}
}