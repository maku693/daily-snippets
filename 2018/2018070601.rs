enum Action {
	Increment,
	Decrement,
}

struct State {
	value: u8,
}

fn update(state: State, action: Action) {
	match action {
		Increment => action += 1;
		Decrement => action -= 1;
	}
}

fn main() {
	let s: State { 0 }
	update(s, Increment);
	update(s, Increment);
	update(s, Decrement);
    println!("{}", s.value);
}
