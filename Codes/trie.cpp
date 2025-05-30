#include <iostream>
#include <map>
#include <vector>
#include <string>
using namespace std;

struct TrieNode {
    map<char, TrieNode*> children;
    bool isEndOfWord = false;
    string intent;  // optional: attach meaning/intent
};

class ChatbotTrie {
    TrieNode* root;

public:
    ChatbotTrie() {
        root = new TrieNode();
    }

    void insert(string phrase, string intent = "") {
        TrieNode* curr = root;
        for (char ch : phrase) {
            if (!curr->children[ch])
                curr->children[ch] = new TrieNode();
            curr = curr->children[ch];
        }
        curr->isEndOfWord = true;
        curr->intent = intent;
    }

    void autocompleteHelper(TrieNode* node, string prefix, vector<string>& suggestions) {
        if (!node) return;
        if (node->isEndOfWord)
            suggestions.push_back(prefix);

        for (auto& it : node->children) {
    char ch = it.first;
    TrieNode* child = it.second;
    autocompleteHelper(child, prefix + ch, suggestions);
}
    }

    vector<string> getSuggestions(string prefix) {
        TrieNode* curr = root;
        for (char ch : prefix) {
            if (!curr->children[ch]) return {}; // No suggestions
            curr = curr->children[ch];
        }
        vector<string> suggestions;
        autocompleteHelper(curr, prefix, suggestions);
        return suggestions;
    }
};

int main() {
    ChatbotTrie chatbot;

    // Training phrases and intents
    chatbot.insert("order status", "Check Order Status");
    chatbot.insert("return policy", "Show Return Policy");
    chatbot.insert("refund status", "Check Refund");
    chatbot.insert("cancel my order", "Cancel Order");
    chatbot.insert("track package", "Track Shipment");
    chatbot.insert("contact support", "Customer Support");

    cout << "Customer Service Chatbot (Type 'exit' to quit)\n";

    string input;
    while (true) {
        cout << "\nYou: ";
        getline(cin, input);
        
        if (input == "exit") break;

        vector<string> suggestions = chatbot.getSuggestions(input);
        if (suggestions.empty()) {
            cout << "Bot: Sorry, I couldn't understand. Can you rephrase?\n";
        } else {
            cout << "Bot Suggestions:\n";
            for (auto& s : suggestions) {
                cout << "- " << s << endl;
            }
        }
    }

    cout << "\nChatbot ended. Have a nice day!\n";
    return 0;
}
