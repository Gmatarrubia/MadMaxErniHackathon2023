export class Status {
	public status: string;
	public speed: number;
	public progress: number;

	constructor(status: string, speed: number, progress: number) {
        this.status = status;
        this.speed = speed;
        this.progress = progress;
    }
}