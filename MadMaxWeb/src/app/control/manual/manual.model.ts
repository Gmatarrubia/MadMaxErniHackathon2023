export class Manual {
	public up: boolean;
	public down: boolean;
	public right: boolean;
	public left: boolean;

	constructor(up: boolean, down: boolean, right: boolean, left: boolean) {
        this.up = up;
        this.down = down;
        this.right = right;
        this.left = left;
    }
}