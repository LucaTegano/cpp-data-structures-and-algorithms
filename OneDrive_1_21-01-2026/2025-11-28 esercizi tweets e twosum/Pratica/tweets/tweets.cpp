#include<string>
#include<iostream>
#include<vector>
#include<unordered_map>
#include<map>
#include<algorithm>
#include<list>
using namespace std;

vector<string> extract_hashtags(const string& tweet) {
	int pos_hash = 0; 
	int pos_space = 0;
	vector<string> hashtags; 
	while (pos_hash != -1) {
		pos_hash = tweet.find("#", pos_hash+1);
		if (pos_hash != -1) {
			pos_space = tweet.find(" ", pos_hash+1);
			hashtags.push_back(tweet.substr(pos_hash, pos_space-pos_hash));
		}
	}
	return hashtags;
}

class Tweet {
public:
	const string text;
	const vector<string> hashtags;

	Tweet(const string& text)
	: text(text)
	, hashtags(extract_hashtags(text)) { }

	bool has_hashtag(const string& hashtag) const {
		return find(hashtags.begin(), hashtags.end(), hashtag) != hashtags.end(); 
	}

	static Tweet read(istream& in) {
		string text; 
		getline(in, text);
		return Tweet(text);
	}
};

bool sort_frequence_pairs(const pair<string, int>& p1, const pair<string, int>& p2) {
	return p1.second < p2.second; 
}


int main() {
	vector<Tweet> tweets;
	int n; 
	cin >> n; 

	
	 //Attenzione cin non pulisce il buffer dopo l'inserimento di n

	// leggo n tweet da input 
	for (int i = 0; i < n; ++i) {
		tweets.push_back(Tweet::read(cin)); 
	}


	// calcolo la frequenza degli hashtag
	map<string, int> hashtag_frequency;
	for (int i = 0; i < n; ++i) {
		for (const string& h: tweets[i].hashtags) {
			hashtag_frequency[h]++;
		}
	}

	// creo & ordino un vettore di (hashtag, frequenza) 
	vector<pair<string,int>> hashtags_with_frequence;
	for (auto i = hashtag_frequency.begin(); i != hashtag_frequency.end(); ++i) {
		hashtags_with_frequence.push_back(make_pair(i->first, i->second));
	}

	// funtore per ordinare i pair (vedi cppreference std::sort)
	sort(hashtags_with_frequence.begin(), hashtags_with_frequence.end(), sort_frequence_pairs);
	for (auto it = hashtags_with_frequence.rbegin(); it != hashtags_with_frequence.rend(); ++it) {
		cout << it->first << ": " << it->second << endl; 
	}

	string hashtag; 
	cin >> hashtag; 

	cout << "All tweets containing the hashtag: " << hashtag << endl; 
	for (const Tweet& t: tweets) {
		if (t.has_hashtag(hashtag)) cout << t.text << endl; 
	}
	return 0;
}

