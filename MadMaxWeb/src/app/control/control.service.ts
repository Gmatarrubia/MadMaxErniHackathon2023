import { Injectable } from '@angular/core';
import { HttpClient, HttpParams } from '@angular/common/http';
import { map, tap, take, exhaustMap } from 'rxjs/operators';

import { CommunicationService } from '../shared/communication.service';

@Injectable()
export class ControlService {
    constructor(private communicationService: CommunicationService) {
    }

    onAutoStart() {
        this.communicationService.getPrueba();
    }

    onAutoStop() {
        this.communicationService.getPrueba();
    }
}