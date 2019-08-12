import Foundation

struct Data: Codable {
    var member1: Int
    var member2: Double
}

// let json = """
// { "member1": 1, "member2": 2.3 }
// """
// try! JSONDecoder().decode(Data.self, from: json.data(using: .utf8)!)
